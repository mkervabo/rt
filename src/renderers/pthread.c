#include "renderers/pthread.h"
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

static void render_tile(t_pthread_renderer *renderer, size_t x, size_t y)
{
	size_t			sub_x;
	size_t			sub_y;
	struct s_ray	ray;
	size_t			pos;

	sub_y = 0;
	while (sub_y < TILE_SIZE && y * TILE_SIZE + sub_y < renderer->w.height)
	{
		sub_x = 0;
		while (sub_x < TILE_SIZE && x * TILE_SIZE + sub_x < renderer->w.width)
		{
			ray = camera_create_ray(renderer->scene->camera, x * TILE_SIZE + sub_x, renderer->w.height - (y * TILE_SIZE + sub_y) - 1, renderer->w);
			pos = (y * TILE_SIZE + sub_y) * renderer->w.width + (x * TILE_SIZE + sub_x);
			renderer->pixels[pos] = color_to_rgb(raytrace(renderer->scene, ray, renderer->hits + pos));
			sub_x++;
		}
		if (atomic_load(&renderer->end))
			break;
		if (renderer->multiple_updates)
			pthread_cond_signal(&renderer->render_update_cond);
		sub_y++;
	}
}

static void	render_tile_loop(t_pthread_renderer *renderer)
{
	size_t			tile;

	while (!atomic_load(&renderer->end))
	{
		if (renderer->block_before) {
			printf("Stop\n");
			pthread_cond_wait(&renderer->start_render_cond, &renderer->start_render_mutex);
		}

		tile = atomic_load(&renderer->last_tile);
		while (!atomic_compare_exchange_weak(&renderer->last_tile, &tile, tile + 1))
			tile = atomic_load(&renderer->last_tile);

		if (tile >= renderer->tiles)
		{
			pthread_cond_wait(&renderer->start_render_cond, &renderer->start_render_mutex);
			continue;
		}

		render_tile(
			renderer, 
			tile % ((renderer->w.width + renderer->w.width - 1) / TILE_SIZE),
			tile / ((renderer->w.width + renderer->w.width - 1) / TILE_SIZE)
		);

		atomic_thread_fence(memory_order_release);
		pthread_mutex_lock(&renderer->render_update_mutex);
		tile = atomic_load(&renderer->tiles_done);
		while (!atomic_compare_exchange_weak(&renderer->tiles_done, &tile, tile + 1))
			tile = atomic_load(&renderer->tiles_done);
		pthread_cond_signal(&renderer->render_update_cond);
		pthread_mutex_unlock(&renderer->render_update_mutex);
	}
}

t_pthread_renderer	create_pthread_renderer(const t_scene *scene, struct s_size window, bool multiple_updates, bool block_before)
{
	return ((struct s_pthread_renderer) {
		.pixels = malloc(sizeof(uint32_t) * window.width * window.height),
		.hits = malloc(sizeof(struct s_pixel_hit) * window.width * window.height),
		.scene = scene,
		.w = window,
		.tiles = ((window.width + window.width - 1) / TILE_SIZE)
			* ((window.height + window.height - 1) / TILE_SIZE),
		.multiple_updates = multiple_updates,
		.render_update_cond = PTHREAD_COND_INITIALIZER,
		.render_update_mutex = PTHREAD_MUTEX_INITIALIZER,
		.block_before = block_before,
		.start_render_cond = PTHREAD_COND_INITIALIZER,
		.start_render_mutex = PTHREAD_MUTEX_INITIALIZER,
	});
}

void				pthread_renderer_create_threads(t_pthread_renderer *renderer, pthread_t threads[], size_t threads_size)
{
	size_t	i;

	atomic_store(&renderer->end, false);
	if (renderer->block_before)
		pthread_mutex_lock(&renderer->start_render_mutex);

	i = 0;
	while (i < threads_size)
	{
		pthread_create(&threads[i], 0, (void *)render_tile_loop, renderer);
		i++;
	}
}

void				pthread_render_continue(t_pthread_renderer *renderer)
{
	pthread_mutex_lock(&renderer->start_render_mutex);
	pthread_cond_signal(&renderer->start_render_cond);
	pthread_mutex_unlock(&renderer->start_render_mutex);
}

uint32_t			*pthread_render(t_pthread_renderer *renderer, t_update_fn update, void *user)
{
	size_t	i;

	pthread_mutex_lock(&renderer->render_update_mutex);
	atomic_store(&renderer->last_tile, 0);
	atomic_store(&renderer->tiles_done, 0);
	pthread_mutex_lock(&renderer->start_render_mutex);
	pthread_cond_broadcast(&renderer->start_render_cond);
	pthread_mutex_unlock(&renderer->start_render_mutex);
	ft_memset(renderer->pixels, 0, sizeof(uint32_t) * renderer->w.width * renderer->w.height);
	while (atomic_load(&renderer->tiles_done) < renderer->tiles)
	{
		pthread_cond_wait(&renderer->render_update_cond, &renderer->render_update_mutex);
		atomic_thread_fence(memory_order_acquire);
		if (update(renderer->pixels, atomic_load(&renderer->tiles_done), user)) {
			pthread_mutex_unlock(&renderer->render_update_mutex);
			atomic_store(&renderer->end, true);
			return (renderer->pixels);
		}
	}
	pthread_mutex_unlock(&renderer->render_update_mutex);
	i = 0;
	while (i < renderer->scene->filters_size)
		apply_filter(renderer->scene->filters[i++], renderer->pixels, renderer->hits, renderer->w);
	update(renderer->pixels, atomic_load(&renderer->tiles_done), user);
	return (renderer->pixels);
}
