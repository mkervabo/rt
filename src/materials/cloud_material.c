#include "cloud_material.h"
#include "noise.h"
#include "color_material.h"
#include "material_types.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "config_utils.h"
#include <math.h>
#include <stdlib.h>

t_color						cloud_material_color(
	struct s_cloud_material *material, t_scene *scene,
	struct s_ray ray, struct s_hit *hit)
{
	double			res;
	double			div;
	uint8_t			i;
	t_vec3			p;

	i = 0;
	res = 0;
	div = 0;
	p = ray_point_at(&ray, hit->t);
	while (i < 8)
	{
		res += material->size[8 - i] * (noise(vec3_multv(p, material->size[i])) + 1) / 2;
		div += material->size[i];
		i++;
	}
	return (color_multv(material_color(material->material, scene, ray, hit), res / div));
}


struct s_cloud_material	*read_cloud_material(t_toml_table *toml)
{
	struct s_cloud_material	*material;
	t_toml			*value;
	uint8_t			i;

	if (!(material = malloc(sizeof(*material))))
		return (NULL);
	if (!read_toml_type(toml, &value, "material", TOML_Table))
		return (nfree(material));
	if (!(material->material = read_material(value->value.table_v)))
		return (nfree(material));
	if (!read_toml_type(toml, &value, "size", TOML_Array))
		return (nfree(material));
	if (value->value.array_v->len != 8)
		return (nfree(material));
	if (value->value.array_v->inner[0].type != TOML_Float)
		return (nfree(material));
	i = 0;
	while (i < 8)
	{
		material->size[i] = value->value.array_v->inner[i].value.float_v;
		i++;
	}
	material->super.type = MATERIAL_CLOUD;
	return (material);
}