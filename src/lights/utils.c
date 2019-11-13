#include "utils.h"
#include "config_utils.h"
#include "raytrace.h"
#include <stdlib.h>

#include <math.h>

#define MAX_DEPTH 5

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
		light->video = (struct s_video_light) { .frame_len = 0 };
	return (true);
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

double		receive_light(struct s_scene *scene, struct s_ray *light, t_vec3 p, t_color *color) {
	struct s_ray	shadow;
	t_vec3			to_light;
	t_vec3			direction;
	double			v;
	struct s_hit	hit;
	t_material		*mat;

	to_light = vec3_sub(light->origin, p);
	v = vec3_length(to_light);
	direction = vec3_divv(to_light, v);
	shadow = (struct s_ray) {
		.origin = p,
		.direction = direction,
		.depth = light->depth + 1
	};
	hit = hit_scene(scene->objects, scene->objects_size, shadow, NULL);
	if (hit.t >= 0 && hit.t <= v)
	{
		if ((v = material_transparency(hit.who->material, &hit, &mat)) != 0.0) {
			if (shadow.depth < MAX_DEPTH)
				*color = material_color(mat, scene, shadow, &hit);
			return (1.0 - v);
		}
		return (0.0);
	}
	return (1.0);
}

void		free_light_super(t_light *light)
{
	free(light->video.frame);
}
