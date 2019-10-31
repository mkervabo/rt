/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 12:34:54 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/11/13 20:27:53 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "object.h"
#include "filter.h"
#include "raytrace.h"
#include "string_utils.h"

#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

#define TILE_SIZE 96
#define NUM_THREADS 5

static pthread_cond_t g_condition = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

static void	render_tile(struct s_thread_arg *ctx, size_t x, size_t y)
{
	size_t			sub_x;
	size_t			sub_y;
	struct s_ray	ray;
	size_t			pos;

	sub_y = 0;
	while (sub_y < TILE_SIZE && y * TILE_SIZE + sub_y < ctx->window.height)
	{
		sub_x = 0;
		while (sub_x < TILE_SIZE && x * TILE_SIZE + sub_x < ctx->window.width)
		{
			ray = camera_create_ray(ctx->scene->camera, x * TILE_SIZE + sub_x,
				ctx->window.height - (y * TILE_SIZE + sub_y) - 1, ctx->window);
			ray.n1 = 1.0;
			pos = (y * TILE_SIZE + sub_y) * ctx->window.width
				+ (x * TILE_SIZE + sub_x);
			ctx->pixels[pos] = color_to_rgb(raytrace(ctx->scene, ray,
				ctx->hits + pos));
			sub_x++;
		}
		pthread_cond_signal(&g_condition);
		sub_y++;
	}
}

static void	render_tiles(struct s_thread_arg *ctx)
{
	size_t			i;
	size_t			max_i;

	max_i = ((ctx->window.width + ctx->window.width - 1) / TILE_SIZE)
		* ((ctx->window.height + ctx->window.height - 1) / TILE_SIZE);
	while (true)
	{
		i = atomic_load(&ctx->i);
		while (!atomic_compare_exchange_weak(&ctx->i, &i, i + 1))
			i = atomic_load(&ctx->i);
		if (i >= max_i)
			break ;
		render_tile(ctx,
			i % ((ctx->window.width + ctx->window.width - 1) / TILE_SIZE),
			i / ((ctx->window.width + ctx->window.width - 1) / TILE_SIZE));
		pthread_mutex_lock(&g_mutex);
		ctx->done++;
		pthread_cond_signal(&g_condition);
		pthread_mutex_unlock(&g_mutex);
	}
}

static bool	init_render(struct s_thread_arg *arg, pthread_t *threads,
	size_t *max_i)
{
	size_t	i;

	if (!(arg->pixels = malloc(sizeof(uint32_t)
			* arg->window.width * arg->window.height)))
		return (false);
	if (!(arg->hits = malloc(sizeof(*arg->hits)
			* arg->window.width * arg->window.height)))
	{
		free(arg->pixels);
		return (false);
	}
	ft_memset(arg->pixels, 0, sizeof(uint32_t)
			* arg->window.width * arg->window.height);
	pthread_mutex_lock(&g_mutex);
	i = 0;
	while (i < NUM_THREADS)
		pthread_create(&threads[i++], 0, (void *)render_tiles, arg);
	*max_i = ((arg->window.width + arg->window.width - 1) / TILE_SIZE)
		* ((arg->window.height + arg->window.height - 1) / TILE_SIZE);
	return (true);
}

void		apply_filters(struct s_thread_arg *arg, t_update_fn update,
	void *user)
{
	size_t	i;

	i = 0;
	while (i < arg->scene->filters_size)
		apply_filter(arg->scene->filters[i++], arg->pixels, arg->hits,
			arg->window);
	free(arg->hits);
	update(arg->pixels, user);
}

uint32_t	*render(t_scene *scene, struct s_size window, t_update_fn update,
	void *user)
{
	size_t				i;
	size_t				max_i;
	struct s_thread_arg	arg;
	pthread_t			threads[NUM_THREADS];

	arg = (struct s_thread_arg) { .scene = scene, .window = window };
	if (!init_render(&arg, threads, &max_i))
		return (NULL);
	while (arg.done < max_i)
	{
		pthread_cond_wait(&g_condition, &g_mutex);
		if (!update(arg.pixels, user))
			continue;
		pthread_mutex_unlock(&g_mutex);
		atomic_store(&arg.i, max_i);
		i = 0;
		while (i < NUM_THREADS)
			pthread_join(threads[i++], NULL);
		free(arg.hits);
		return (arg.pixels);
	}
	pthread_mutex_unlock(&g_mutex);
	apply_filters(&arg, update, user);
	return (arg.pixels);
}
