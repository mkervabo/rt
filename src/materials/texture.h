#ifndef MATERIALS_TEXTURE_H
# define MATERIALS_TEXTURE_H

# include "material.h"
# include <SDL.h>

struct s_texture {
	t_material	super;
	SDL_Surface	*surface;
};

t_color						texture_color(struct s_texture *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_texture	*read_texture(t_toml_table *toml);

#endif
