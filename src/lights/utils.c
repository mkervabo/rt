#include "utils.h"
#include "config_utils.h"
#include "raytrace.h"
#include "../materials/reflection_material.h"
#include "../materials/material_types.h"

#include <math.h>

bool		read_light_super(t_toml_table *toml, t_light *light)
{
	t_toml		*value;

	if (!(value = table_get(toml, "intensity")))
		light->intensity = 1;
	else if (!read_digit(value, &light->intensity))
		return ((bool)rt_error(NULL, "intensity is not a number"));
	if (!(value = table_get(toml, "decay")))
		light->decay = 0;
	else if (!read_digit(value, &light->decay))
		return ((bool)rt_error(NULL, "decay is not a number"));
	if (!(value = table_get(toml, "color")))
		light->color = (t_color) { 255, 255, 255 };
	else if (!read_color(value->value.table_v, &light->color))
		return ((bool)rt_error(NULL, "Invalid color in read light super"));
	if (!read_video_light(toml, &light->video))
		light->video.frame_len = 0;
	return (true);
}

static bool	refracted_light(double *value, struct s_reflection_material *material)
{
	if (material->transparency > 0)
	{
		*value = material->transparency / 100;
		return (true);
	}
	return (false);
}

double	light_decay(t_vec3 origin, t_vec3 point, double decay)
{
	t_vec3		to_light;
	double		dist;
	double		res;

	to_light = vec3_sub(origin, point);
	dist = vec3_length(to_light);
	res = 1 / pow(dist, decay);
	return (res);
}

bool		receive_light(t_scene *scene, struct s_ray *light, t_vec3 p, double *value) {
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
	hit = hit_scene(scene->objects, scene->objects_size, shadow, NULL);

	if (hit.t >= 0 && hit.t <= dist)
	{
		if (hit.who->material->type == MATERIAL_REFLECTION)
			if (refracted_light(value, (struct s_reflection_material *)hit.who->material))
				return (true);
		return (false);
	}
	return (true);
}

