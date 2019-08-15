#ifndef MATERIALS_REFLECTION_MATERIAL_H
# define MATERIALS_REFLECTION_MATERIAL_H

# include "material.h"

struct s_reflection_material {
	t_material	super;
	double		reflection;
	double		transparency;
	double		refraction;
	t_material	*color;
};

t_color							reflection_material_color(struct s_reflection_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_reflection_material	*read_reflection_material(t_toml_table *toml);

#endif
