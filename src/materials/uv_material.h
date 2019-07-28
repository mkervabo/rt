#ifndef MATERIALS_UV_MATERIAL_H
# define MATERIALS_UV_MATERIAL_H

# include "material.h"

struct s_uv_material {
	t_material	super;
};

t_color						uv_material_color(struct s_uv_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_uv_material	*read_uv_material(t_toml_table *toml);

#endif
