#ifndef MATERIALS_HEIGHT_MAP_H
# define MATERIALS_HEIGHT_MAP_H

# include "material.h"
# include <SDL.h>

struct s_height_map
{
	t_material	super;
	SDL_Surface	*surface;
	t_material	*material;
};

t_color						height_map_color(struct s_height_map *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_height_map			*read_height_map(t_toml_table *toml);

#endif
