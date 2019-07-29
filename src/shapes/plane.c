#include "plane.h"
#include "shape_types.h"
#include "utils.h"
#include "math/quadratic.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>

struct s_hit hit_plane(struct s_ray ray, struct s_plane *plane,
		struct s_intersection_tab *intersections)
{
	if (fabs(ray.direction.y) < 1e-6)
		return ((struct s_hit) { .t = -1.0 });

	double t = -ray.origin.y / ray.direction.y;

	if (t < 0)
		return ((struct s_hit) { .t = -1.0 });

	t_vec3 p = ray_point_at(&ray, t);
	return ((struct s_hit) {
		.t = t,
		.normal = vec3(0, 1, 0),
		.u = fmod(fabs(p.x), 1),
		.v = fmod(fabs(p.z), 1)
	});
}

struct s_plane	*read_plane(t_toml_table *toml)
{
	struct s_plane	*plane;

	if (!(plane = malloc(sizeof(*plane))))
		return (NULL);
	if (!read_shape_super(toml, &plane->super))
		return (nfree(plane));
	plane->super.type = SHAPE_PLANE;
	return (plane);
}
