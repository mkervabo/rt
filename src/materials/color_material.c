#include "color_material.h"
#include "material_types.h"
#include "config_utils.h"
#include <stdlib.h>

t_color		color_material_color(struct s_color_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	(void)scene;
	(void)ray;
	(void)hit;
	return (material->color);
}

double	color_material_transparency(struct s_color_material *material)
{
	(void)material;
	return (0.0);
}

struct s_color_material	*read_color_material(t_toml_table *toml)
{
	struct s_color_material	*material;
	t_toml					*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate color material"));
	if (read_toml_type(toml, &value, "color", TOML_Table) == false)
		material->color = (t_color) { 0, 0, 0 };
	else if (!read_color(value->value.table_v, &material->color))
		return (rt_error(material, "Invalid color material"));
	material->super.type = MATERIAL_COLOR;
	return (material);
}
