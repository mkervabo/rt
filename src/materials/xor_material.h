#ifndef MATERIALS_XOR_MATERIAL_H
# define MATERIALS_XOR_MATERIAL_H

# include "material.h"
#include <stdbool.h>

struct s_xor_material {
	t_material	super;
	bool		color;
};

double						xor_material_transparency(struct s_xor_material *material, struct s_hit *hit);
t_color						xor_material_color(struct s_xor_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_xor_material		*read_xor_material(t_toml_table *toml);
void						free_xor_material(struct s_xor_material *material);

#endif
