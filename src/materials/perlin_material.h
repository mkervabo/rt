#ifndef MATERIALS_PERLIN_MATERIAL_H
# define MATERIALS_PERLIN_MATERIAL_H

# include "material.h"

struct s_perlin_material {
	t_material	super;
	double		size;
	t_material	*material;
};

t_color							perlin_material_color(struct s_perlin_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_perlin_material		*read_perlin_material(t_toml_table *toml);

#endif
