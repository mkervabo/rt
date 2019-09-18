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

static bool	read_color(t_toml_table *toml, t_color *color)
{
	t_toml	*value;

	if (!(value = table_get(toml, "r")))
		color->r = 0;
	else if (value->type != TOML_Integer)
		return ((bool)rt_error(NULL, "Is not a interger in red color"));
	else
		color->r = value->value.integer_v;
	if (!(value = table_get(toml, "g")))
		color->g = 0;
	else if (value->type != TOML_Integer)
		return ((bool)rt_error(NULL, "Is not a interger in green color"));
	else
		color->g = value->value.integer_v;
	if (!(value = table_get(toml, "b")))
		color->b = 0;
	else if (value->type != TOML_Integer)
		return ((bool)rt_error(NULL, "Is not a interger in blue color"));
	else
		color->b = value->value.integer_v;
	return (true);
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
