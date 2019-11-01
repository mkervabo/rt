#include "raytrace.h"
#include "material.h"
#include <math.h>

struct s_hit	hit_scene(t_object *objects, size_t object_size, struct s_ray ray)
{
	struct s_hit	max;
	struct s_hit	hit;
	size_t			i;

	i = 0;
	max = (struct s_hit) {
		.t = -1.0
	};
	while (i < object_size)
	{
		hit = hit_shape(ray, objects[i].shape, NULL);
		if (hit.who == NULL)
			hit.who = objects + i;
		if (hit.t >= 0 && (max.t < 0 || hit.t <= max.t))
			max = hit;
		i++;
	}
	return (max);
}

t_color	raytrace(t_scene *scene, struct s_ray ray, struct s_pixel_hit *pixel_hit)
{
	struct s_hit	hit;

	hit = hit_scene(scene->objects, scene->objects_size, ray);
	if (pixel_hit)
	{
		pixel_hit->t = hit.t;
		if (pixel_hit->t >= 0)
			pixel_hit->t *= fabs(vec3_dot(ray.direction, vec3_rotate(vec3(0, 0, -1), scene->camera->rotation)));
		pixel_hit->who = hit.who;
	}
	if (hit.t >= 0)
		return (material_color(hit.who->material, scene, ray, &hit));
	else
		return ((t_color) {
			.r = fabs(ray.direction.x) * 255,
			.g = fabs(ray.direction.y) * 255,
			.b = fabs(ray.direction.z) * 255
		});
}
