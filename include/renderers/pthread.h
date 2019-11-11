#ifndef RENDERERS_PTHREAD_H
# define RENDERERS_PTHREAD_H

# include "math/size.h"
# include "scene.h"

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdatomic.h>

# define TILE_SIZE 96

typedef struct		s_pthread_renderer {
	uint32_t			*pixels;
	struct s_pixel_hit	*hits;

	const t_scene		*scene;
	struct s_size		w;

	atomic_size_t		last_tile;
	atomic_size_t		tiles_done;
	size_t				tiles;

	atomic_bool			end;

	bool				multiple_updates;
	pthread_cond_t		render_update_cond;
	pthread_mutex_t		render_update_mutex;

	bool				block_before;
	pthread_cond_t		start_render_cond;
	pthread_mutex_t		start_render_mutex;
}					t_pthread_renderer;

typedef bool		(*t_update_fn)(uint32_t *pixels, size_t tiles_done, void *user);

t_pthread_renderer	create_pthread_renderer(const t_scene *scene, struct s_size window, bool multiple_updates, bool block_before);

void				pthread_render_continue(t_pthread_renderer *renderer);

void				pthread_renderer_create_threads(t_pthread_renderer *renderer, pthread_t threads[], size_t threads_size);

uint32_t			*pthread_render(t_pthread_renderer *renderer, t_update_fn update, void *user);
#endif
