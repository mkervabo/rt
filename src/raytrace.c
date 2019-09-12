#include "raytrace.h"
#include "material.h"
#include <math.h>

struct s_hit	hit_scene(t_scene *scene, struct s_ray ray)
{
	struct s_hit	max;
	struct s_hit	hit;
	size_t			i;

	i = 0;
	max = (struct s_hit) {
		.t = -1.0
	};
	while (i < scene->objects_size)
	{
		hit = hit_shape(ray, scene->objects[i].shape, NULL);
		hit.who = scene->objects + i;
		if (hit.t >= 0 && (max.t < 0 || hit.t <= max.t))
			max = hit;
		i++;
	}
	return (max);
}

t_color	raytrace(t_scene *scene, struct s_ray ray, struct s_pixel_hit *pixel_hit)
{
	struct s_hit	hit;

	hit = hit_scene(scene, ray);
	if (pixel_hit)
	{
		pixel_hit->t = hit.t;
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
