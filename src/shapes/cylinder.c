#include "cylinder.h"
#include "sphere.h"
#include "shape_types.h"
#include "utils.h"
#include "math/quadratic.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>

struct s_hit hit_cylinder(struct s_ray ray, struct s_cylinder *cylinder,
		struct s_intersection_tab *intersections)
{
	struct s_sphere	sphere;
	struct s_hit	hit;
	struct s_ray	r;

	r = ray;
	ray.direction.y = 0;
	ray.origin.y = 0;
	sphere = (struct s_sphere) {
		.r = cylinder->r
	};
	hit = hit_sphere(ray, &sphere, intersections);
	if (hit.t >= 0)
		hit.v = fmod(fabs(r.direction.y * hit.t + r.origin.y), 1);
	return (hit);
}

struct s_cylinder	*read_cylinder(t_toml_table *toml)
{
	struct s_cylinder	*cylinder;
	t_toml				*radius;

	if (!(cylinder = malloc(sizeof(*cylinder))))
		return (NULL);
	if (!(radius = table_get(toml, "radius")))
		return (nfree(cylinder));
	if (!read_shape_super(toml, &cylinder->super))
		return (nfree(cylinder));
	if (read_digit(radius, &cylinder->r) == false)
		return (nfree(cylinder));
	cylinder->super.type = SHAPE_CYLINDER;
	return (cylinder);
}
