#ifndef RENDERERS_PTHREAD_H
# define RENDERERS_PTHREAD_H

# include "math/size.h"
# include "config.h"

typedef bool		(*t_update_fn)(uint32_t *pixels, void *user);

uint32_t			*network_render(struct s_config *config, t_update_fn update, void *user);

#endif
