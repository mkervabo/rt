#ifndef RENDER_H
# define RENDER_H

# include "math/size.h"
# include "scene.h"
# include <stdint.h>
# include <stdbool.h>

typedef bool	(*t_update_fn)(uint32_t *pixels, void *user);

uint32_t		*render(t_scene *scene, struct s_size window, t_update_fn update, void *user);
#endif
