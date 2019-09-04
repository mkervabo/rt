/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 12:34:54 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/10/26 13:04:31 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "object.h"
#include "filter.h"
#include "raytrace.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

static void		*ft_memset(void *s, int c, size_t n)
{
	while (n--)
		((unsigned char *)s)[n] = c;
	return (s);
}

#define TILE_SIZE 96

static pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct s_thread_arg {
	uint32_t		*pixels;
	struct s_pixel_hit	*hits;
	t_scene			*scene;
	struct s_size		window;
	atomic_size_t		*i;
	size_t			*done;
};

static void	render_tile(struct s_thread_arg *ctx)
{
	size_t			i;
	size_t			max_i;
	size_t			x;
	size_t			y;
	size_t			sub_x;
	size_t			sub_y;
	struct s_ray		ray;
	size_t			pos;

	max_i = ((ctx->window.width + ctx->window.width - 1) / TILE_SIZE) * ((ctx->window.height + ctx->window.height - 1) / TILE_SIZE);
	while (true)
	{
		i = atomic_load(ctx->i);
		while (!atomic_compare_exchange_weak(ctx->i, &i, i + 1))
			i = atomic_load(ctx->i);

		if (i >= max_i)
			break;

		x = i % ((ctx->window.width + ctx->window.width - 1) / TILE_SIZE);
		y = i / ((ctx->window.width + ctx->window.width - 1) / TILE_SIZE);

		sub_y = 0;
		while (sub_y < TILE_SIZE && y * TILE_SIZE + sub_y < ctx->window.height)
		{
			sub_x = 0;
			while (sub_x < TILE_SIZE && x * TILE_SIZE + sub_x < ctx->window.width)
			{
				ray = camera_create_ray(ctx->scene->camera, x * TILE_SIZE + sub_x, ctx->window.height - (y * TILE_SIZE + sub_y) - 1, ctx->window);
				ray.n1 = 1.0;
				pos = (y * TILE_SIZE + sub_y) * ctx->window.width + (x * TILE_SIZE + sub_x);
				ctx->pixels[pos] = color_to_rgb(raytrace(ctx->scene, ray, ctx->hits + pos));
				sub_x++;
			}
			sub_y++;
		}
		pthread_mutex_lock(&mutex);
		(*ctx->done)++;
		pthread_cond_signal(&condition);
		pthread_mutex_unlock(&mutex);
	}
}

#define NUM_THREADS 4

uint32_t	*render(t_scene *scene, struct s_size window, t_update_fn update, void *user)
{
	size_t			i;
	uint32_t		*pixels;
	struct s_pixel_hit	*hits;
	atomic_size_t		atom;
	size_t			done;
	struct s_thread_arg	args[NUM_THREADS];
	pthread_t		threads[NUM_THREADS];

	atomic_init(&atom, 0);
	if (!(pixels = malloc(sizeof(uint32_t) * window.width * window.height)))
		return (NULL);
	if (!(hits = malloc(sizeof(*hits) * window.width * window.height)))
		return (NULL);
	ft_memset(pixels, 0, sizeof(uint32_t) * window.width * window.height);

	done = 0;
	pthread_mutex_lock(&mutex);
	i = 0;
	while (i < NUM_THREADS)
	{
		args[i] = (struct s_thread_arg){
			.pixels = pixels,
			.hits = hits,
			.scene = scene,
			.window = window,
			.i = &atom,
			.done = &done
		};
		pthread_create(&threads[i], 0, render_tile, args + i);
		i++;
	}
	size_t max_i = ((window.width + window.width - 1) / TILE_SIZE) * ((window.height + window.height - 1) / TILE_SIZE);
	while (done < max_i)
	{
		pthread_cond_wait(&condition, &mutex);
		if (update(pixels, user)) {
			pthread_mutex_unlock(&mutex);
			atomic_store(&atom, max_i);
			i = 0;
			while (i < NUM_THREADS)
				pthread_join(threads[i++], NULL);
			return (pixels);
		}
	}
	pthread_mutex_unlock(&mutex);
	i = 0;
	if (scene->filters)
		while (i < scene->filters_size)
			apply_filter(scene->filters[i++], pixels, hits, window);
	update(pixels, user);
	return (pixels);
}
