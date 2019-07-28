#include "uv_material.h"
#include "material_types.h"
#include <stdlib.h>

t_color						uv_material_color(struct s_uv_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	return ((t_color) {
		.r = hit->u * 255,
		.g = hit->v * 255,
		.b = 0
	});

}

struct s_uv_material	*read_uv_material(t_toml_table *toml)
{
	struct s_uv_material	*material;

	if (!(material = malloc(sizeof(*material))))
		return (NULL);
	material->super.type = MATERIAL_UV;
	return (material);
}
