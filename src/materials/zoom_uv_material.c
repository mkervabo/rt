#include "zoom_uv_material.h"
#include "material_types.h"
#include "config_utils.h"
#include <stdlib.h>

t_color						zoom_uv_material_color(struct s_zoom_uv_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	hit->u *= material->zoom;
	hit->v *= material->zoom;
	return(material_color(material->material, scene, ray, hit));
}

struct s_zoom_uv_material	*read_zoom_uv_material(t_toml_table *toml)
{
	struct s_zoom_uv_material	*material;
	t_toml						*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate uv material"));
	if (!(value = table_get(toml, "zoom")))
		material->zoom = 0;
	else if (read_digit(value, &material->zoom) == false)
		return (rt_error(NULL, "Invalid zoom in move uv material"));
	if (read_toml_type(toml, &value, "material", TOML_Table) == false)
		return (rt_error(material, "Missing material in zoom uv material"));
	else if (!(material->material = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid material in zoom uv material"));
	material->super.type = MATERIAL_ZOOM_UV;
	return (material);
}
