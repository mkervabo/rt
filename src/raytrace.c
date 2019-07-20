#include "raytrace.h"
#include <math.h>

struct s_hit	hit(t_scene *scene, struct s_ray ray) {
	struct s_hit	max;
	struct s_hit	hit;
	size_t	i;

	i = 0;
	max = (struct s_hit) {
		.t = -1.0
	};
	while (i < scene->objects_size)
	{
		hit = hit_shape(ray, scene->objects[i], NULL);
		if (hit.t >= 0 && (max.t < 0 || hit.t <= max.t))
			max = hit;
		i++;
	}
	return (max);
}

t_color	raytrace(t_scene *scene, struct s_ray ray) {
	if (hit(scene, ray).t >= 0)
		return ((t_color) { 255, 0, 0});
	else
		return ((t_color) {
			.r = fabs(ray.direction.x) * 255,
			.g = fabs(ray.direction.y) * 255,
			.b = fabs(ray.direction.z) * 255
		});
}
