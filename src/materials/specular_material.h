#ifndef MATERIALS_SPECULAR_MATERIAL_H
# define MATERIALS_SPECULAR_MATERIAL_H

# include "material.h"

struct s_specular_material {
	t_material	super;
	t_material	*material;
	double		n;
	double		k;
};

t_color							specular_material_color(struct s_specular_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_specular_material			*read_specular_material(t_toml_table *toml);

#endif
