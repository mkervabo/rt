#include "diffuse_material.h"
#include "raytrace.h"
#include "material_types.h"
#include "config_utils.h"

#include "reflection_material.h"

#include <stdlib.h>
#include <math.h>

static bool	refracted_light(double *value, struct s_reflection_material *material)
{
	if (material->transparency > 0)
	{
		*value = material->transparency / 100;
		return (true);
	}
	return (false);
}

static double	light_decay(t_vec3 origin, t_vec3 point, double decay)
{
	t_vec3		to_light;
	double		dist;
	double		res;

	to_light = vec3_sub(origin, point);
	dist = vec3_length(to_light);
	res = 1 / pow(dist, decay);
	return (res);
}

static bool		receive_light(t_scene *scene, struct s_ray *light, t_vec3 p, double *value) {
	struct s_ray	shadow;
	t_vec3			to_light;
	t_vec3			direction;
	double			dist;
	struct s_hit	hit;

	to_light = vec3_sub(light->origin, p);
	dist = vec3_length(to_light);
	direction = vec3_divv(to_light, dist);
	shadow = (struct s_ray) {
		.origin = p,
		.direction = direction
	};
	hit = hit_scene(scene->objects, scene->objects_size, shadow);

	if (hit.t >= 0 && hit.t <= dist)
	{
		if (hit.who->material->type == MATERIAL_REFLECTION)
			if (refracted_light(value, (struct s_reflection_material *)hit.who->material))
				return (true);
		else
			return (false);
	}
	return (true);
}

# define SHADOW_BIAS 1e-4

t_color			diffuse_material_color(struct s_diffuse_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	size_t				i;
	struct s_ray		lray;
	t_color				light_color;
	double				intensity;
	t_vec3				point;
	double				value;

	value = 1.0;
	point = vec3_add(ray_point_at(&ray, hit->t), vec3_multv(hit->normal, SHADOW_BIAS));
	light_color = (t_color){ 0, 0, 0 };
	i = 0;
	while (i < scene->lights_size) {
		lray = get_light_ray(scene->lights[i], ray_point_at(&ray, hit->t));
		if (vec3_is_zero(lray.direction))
			intensity = /*scene->lights[i]->intensity*/0;
		else if (receive_light(scene, &lray, point, &value))
		{
			intensity = material->albedo / M_PI * fmax(vec3_dot(vec3_multv(lray.direction, -1), hit->normal), 0)
			* scene->lights[i]->intensity * value * light_decay(lray.origin, point, scene->lights[i]->decay);
		}
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
	t_toml					*value;

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
