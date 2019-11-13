#include "specular_material.h"
#include "raytrace.h"
#include "material_types.h"
#include "config_utils.h"
#include "math/utils.h"

#include "reflection_material.h"

#include <stdlib.h>
#include <math.h>

t_color			specular_material_color(struct s_specular_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	size_t				i;
	struct s_ray		lray;
	t_color				light_color;
	double				intensity;
	t_vec3				point;
	double				value;
	t_color				color;

	point = vec3_add(ray_point_at(&ray, hit->t), vec3_multv(hit->normal, SHADOW_BIAS));
	light_color = (t_color){ 0, 0, 0 };
	i = 0;
	lray.depth = ray.depth;
	while (i < scene->lights_size) {
		color = (t_color) { 255, 255, 255 };
		if (!get_light_ray(scene->lights[i], point, &lray))
			intensity = 0;
		else if (vec3_is_zero(lray.direction))
			intensity = 0;
		else if ((value = receive_light(scene, &lray, point, &color)) != 0)
		{
			t_vec3 r = vec3_sub(vec3_multv(hit->normal, 2 * vec3_dot(hit->normal, lray.direction)), lray.direction);
			intensity = clamp(scene->lights[i]->intensity * pow(vec3_dot(vec3_multv(ray.direction, -1), r), material->n), 0, 1) * value;
		}
		else
			intensity = 0;
		light_color = color_add(light_color, color_multv(
			color_ratio(scene->lights[i]->color, color),
			intensity
		));
		i++;
	}
	return (color_add(
		material_color(material->material, scene, ray, hit),
		color_multv(light_color, material->k)
	));
}

double	specular_material_transparency(struct s_specular_material *material, struct s_hit *hit, t_material **color)
{
	return (material_transparency(material->material, hit, color));
}

struct s_specular_material	*read_specular_material(t_toml_table *toml)
{
	struct s_specular_material	*material;
	t_toml					*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate specular material"));
	if (!(value = table_get(toml, "n")))
		material->n = 2;
	else if (!read_digit(value, &material->n))
		return (rt_error(material, "Invalid n in specular material"));
	if (!(value = table_get(toml, "k")))
		material->k = 1;
	else if (!read_digit(value, &material->k))
		return (rt_error(material, "Invalid k in specular material"));
	if (material->k > 1 || material->k < 0)
		return (rt_error(material, "k must be between 0-1 in specular material"));
	if (!read_toml_type(toml, &value, "material", TOML_Table))
		return (rt_error(material, "Missing material in specular material"));
	if (!(material->material = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid material in specular material"));
	material->super.type = MATERIAL_SPECULAR;
	return (material);
}

void						free_specular_material(struct s_specular_material *material)
{
	free_material(material->material);
	free(material);
}
