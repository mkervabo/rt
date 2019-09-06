#ifndef MATERIALS_CARTOON_MATERIAL_H
# define MATERIALS_CARTOON_MATERIAL_H

# include "material.h"

struct s_cartoon_material {
	t_material	super;
	t_material	*material;
	double		albedo;
};

t_color							cartoon_material_color(struct s_cartoon_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_cartoon_material		*read_cartoon_material(t_toml_table *toml);

#endif
