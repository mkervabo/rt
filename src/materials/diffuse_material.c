#include "diffuse_material.h"
#include "material_types.h"
#include "config_utils.h"

#include <stdlib.h>
#include <math.h>


t_color			diffuse_material_color(struct s_diffuse_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	size_t				i;
	struct s_ray		lray;
	t_color				light_color;
	double				intensity;
	t_vec3				point;
	double				value;

	point = vec3_add(ray_point_at(&ray, hit->t), vec3_multv(hit->normal, SHADOW_BIAS));
	light_color = (t_color){ 0, 0, 0 };
	i = 0;
	while (i < scene->lights_size) {
		value = 1.0;
		if (get_light_ray(scene->lights[i], ray_point_at(&ray, hit->t), &lray) == false)
			intensity = 0;
		else if (vec3_is_zero(lray.direction))
			intensity = scene->lights[i]->intensity;
		else if (receive_light(scene, &lray, point, &value))
			intensity = material->albedo / M_PI * fmax(vec3_dot(vec3_multv(lray.direction, -1), hit->normal), 0)
				* scene->lights[i]->intensity * value * light_decay(lray.origin, point, scene->lights[i]->decay);
		else
			intensity = 0;
		light_color = color_add(light_color, color_multv(
			scene->lights[i]->color,
			intensity
		));
		i++;
	}
	return (color_ratio(
		material_color(material->material, scene, ray, hit),
		light_color
	));
}

struct s_diffuse_material	*read_diffuse_material(t_toml_table *toml)
{
	struct s_diffuse_material	*material;
	t_toml						*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate color material"));
	if (!(value = table_get(toml, "albedo")))
		return (rt_error(material, "Missing albedo in color material"));
	if (!read_digit(value, &material->albedo))
		return (rt_error(material, "Invalid albedo in color material"));
	if (!read_toml_type(toml, &value, "material", TOML_Table))
		return (rt_error(material, "Missing material in color material"));
	if (!(material->material = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid material in color material"));
	material->super.type = MATERIAL_DIFFUSE;
	return (material);
}
