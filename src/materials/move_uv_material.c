#include "move_uv_material.h"
#include "material_types.h"
#include "config_utils.h"
#include <stdlib.h>

t_color						move_uv_material_color(struct s_move_uv_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	hit->u += material->u;
	hit->v += material->v;
	return(material_color(material->material, scene, ray, hit));
}

double	move_uv_material_transparency(struct s_move_uv_material *material, struct s_hit *hit, t_material **color)
{
	return (material_transparency(material->material, hit, color));
}

struct s_move_uv_material	*read_move_uv_material(t_toml_table *toml)
{
	struct s_move_uv_material	*material;
	t_toml						*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate uv material"));
	if (!(value = table_get(toml, "u")))
		material->u = 0;
	else if (read_digit(value, &material->u) == false)
		return (rt_error(NULL, "Invalid u in move uv material"));
	if (!(value = table_get(toml, "v")))
		material->v = 0;
	else if (read_digit(value, &material->v) == false)
		return (rt_error(NULL, "Invalid v in move uv material"));
	if (read_toml_type(toml, &value, "material", TOML_Table) == false)
		return (rt_error(material, "Missing material in move uv material"));
	else if (!(material->material = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid material in move uv material"));
	material->super.type = MATERIAL_MOVE_UV;
	return (material);
}
