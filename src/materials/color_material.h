#ifndef MATERIALS_COLOR_MATERIAL_H
# define MATERIALS_COLOR_MATERIAL_H

# include "material.h"

struct s_color_material {
	t_material	super;
	t_color		color;
};

t_color							color_material_color(struct s_color_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_color_material			*read_color_material(t_toml_table *toml);

#endif