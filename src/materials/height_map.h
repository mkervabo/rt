#ifndef MATERIALS_HEIGHT_MAP_H
# define MATERIALS_HEIGHT_MAP_H

# include "material.h"
# include "image.h"

struct s_height_map
{
	t_material	super;
	t_image		image;
	t_material	*material;
};

t_color						height_map_color(struct s_height_map *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
double						height_map_transparency(struct s_height_map *material, struct s_hit *hit, t_material **color);
struct s_height_map			*read_height_map(t_toml_table *toml);
void						free_height_map(struct s_height_map *material);

#endif
