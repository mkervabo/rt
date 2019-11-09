#ifndef RENDERERS_PTHREAD_H
# define RENDERERS_PTHREAD_H

# include "math/size.h"
# include "scene.h"

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdatomic.h>

typedef struct		s_pthread_renderer {
	uint32_t			*pixels;
	struct s_pixel_hit	*hits;

	const t_scene		*scene;
	struct s_size		w;

	atomic_size_t		last_tile;
	size_t				tiles_done;
	size_t				tiles;

	atomic_bool			end;

	pthread_cond_t		render_update_cond;
	pthread_mutex_t		render_update_mutex;

	bool				block_before;
	pthread_cond_t		start_render_cond;
	pthread_mutex_t		start_render_mutex;
}					t_pthread_renderer;

typedef bool		(*t_update_fn)(uint32_t *pixels, void *user);

t_pthread_renderer	create_pthread_renderer(const t_scene *scene, struct s_size window, bool block_before);

void				pthread_render_next_tile(t_pthread_renderer *renderer);

void				pthread_renderer_create_threads(t_pthread_renderer *renderer, pthread_t threads[], size_t threads_size);

uint32_t			*pthread_render(t_pthread_renderer *renderer, t_update_fn update, void *user);
#endif
