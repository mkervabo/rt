#ifndef MATERIALS_CLOUD_MATERIAL_H
# define MATERIALS_CLOUD_MATERIAL_H

# include "material.h"

struct s_cloud_material {
	t_material	super;
	double		size[8];
	t_material	*material;
};

t_color							cloud_material_color(struct s_cloud_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_cloud_material		*read_cloud_material(t_toml_table *toml);

#endif
