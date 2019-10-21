#ifndef MATERIALS_MOVE_UV_MATERIAL_H
# define MATERIALS_MOVE_UV_MATERIAL_H

# include "material.h"

struct s_move_uv_material
{
	t_material	super;
	double		u;
	double		v;
	t_material	*material;
};

t_color						move_uv_material_color(struct s_move_uv_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_move_uv_material	*read_move_uv_material(t_toml_table *toml);

#endif
