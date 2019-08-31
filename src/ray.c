#include "ray.h"

struct s_vec3 ray_point_at(const struct s_ray *ray, float t)
{
	return vec3_add(ray->origin, vec3_multv(ray->direction, t));
}
