#ifndef MATERIALS_NORMAL_MATERIAL_H
# define MATERIALS_NORMAL_MATERIAL_H

# include "material.h"

struct s_normal_material {
	t_material	super;
};

t_color						normal_material_color(struct s_normal_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
double						normal_material_transparency(struct s_normal_material *material, struct s_hit *hit);
struct s_normal_material	*read_normal_material(t_toml_table *toml);
void						free_normal_material(struct s_normal_material *material);

#endif
