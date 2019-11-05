#include "cartoon_material.h"
#include "material_types.h"
#include "config_utils.h"
#include "material.h"

#include <stdlib.h>
#include <math.h>

t_color						cartoon_material_color(struct s_cartoon_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
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
	while (i < scene->lights_size) {
		color = (t_color) { 255, 255, 255 };
		if (get_light_ray(scene->lights[i], point, &lray) == false)
			intensity = 0;
		else if (vec3_is_zero(lray.direction))
			intensity = scene->lights[i]->intensity;
		else if ((value = receive_light(scene, &lray, point, &color)) != 0)
			intensity = fmin(material->albedo / M_PI * fmax(vec3_dot(vec3_multv(lray.direction, -1), hit->normal), 0)
				* scene->lights[i]->intensity * value * light_decay(lray.origin, point, scene->lights[i]->decay), 1);
		else
			intensity = 0;
		if (intensity <= 0.01)
			intensity = 0;
		else if (intensity <= 0.2)
			intensity = 0.4;
		else if (intensity <= 0.6)
			intensity = 0.6;
		else
			intensity = 1;
		light_color = color_add(light_color, color_multv(
			color_ratio(scene->lights[i]->color, color),
			intensity
		));
		i++;
	}
	return (color_ratio(
		material_color(material->material, scene, ray, hit),
		light_color
	));
}

double	cartoon_material_transparency(struct s_cartoon_material *material, struct s_hit *hit, t_material **color)
{
	return (material_transparency(material->material, hit, color));
}

struct s_cartoon_material	*read_cartoon_material(t_toml_table *toml)
{
	struct s_cartoon_material	*material;
	t_toml						*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate cartoon material"));
	if (!(value = table_get(toml, "albedo")))
		return (rt_error(material, "Missing albedo in cartoon material"));
	if (!read_digit(value, &material->albedo))
		return (rt_error(material, "Invalid albedo in cartoon material"));
	if (!read_toml_type(toml, &value, "material", TOML_Table))
		return (rt_error(material, "Missing material in cartoon material"));
	if (!(material->material = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid material in cartoon material"));
	material->super.type = MATERIAL_CARTOON;
	return (material);
}

void						free_cartoon_material(struct s_cartoon_material *material)
{
	free_material(material->material);
	free(material);
}