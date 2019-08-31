#ifndef MATERIALS_DIFFUSE_MATERIAL_H
# define MATERIALS_DIFFUSE_MATERIAL_H

# include "material.h"

struct s_diffuse_material {
	t_material	super;
	t_material	*material;
	double		albedo;
};

t_color							diffuse_material_color(struct s_diffuse_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_diffuse_material			*read_diffuse_material(t_toml_table *toml);

#endif
