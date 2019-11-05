#ifndef MATERIALS_ZOOM_UV_MATERIAL_H
# define MATERIALS_ZOOM_UV_MATERIAL_H

# include "material.h"

struct s_zoom_uv_material
{
	t_material	super;
	double		zoom;
	t_material	*material;
};

t_color						zoom_uv_material_color(struct s_zoom_uv_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
double						zoom_uv_material_transparency(struct s_zoom_uv_material *material, struct s_hit *hit, t_material **color);
struct s_zoom_uv_material	*read_zoom_uv_material(t_toml_table *toml);
void						free_zoom_uv_material(struct s_zoom_uv_material *material);

#endif
