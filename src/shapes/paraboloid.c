#include "paraboloid.h"
#include "shape_types.h"
#include "utils.h"
#include "math/quadratic.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>

struct s_hit	hit_paraboloid(struct s_ray ray, struct s_paraboloid *paraboloid,
		struct s_intersection_tab *intersections)
{
	struct s_quadratic		fn;
	struct s_intersection	intersection;
	t_vec3					n;
	double					k;

	if (paraboloid->r == 0)
		return ((struct s_hit) { .t = -1.0 });
	double direction_y = ray.direction.y;
	double origin_y = ray.direction.y;
	ray.direction.y = 0;
	ray.origin.y = 0;
	k = paraboloid->h / (paraboloid->r * paraboloid->r);
	fn.a = k * vec3_dot(ray.direction, ray.direction);
	fn.b = 2 * k * vec3_dot(ray.origin, ray.direction) - direction_y;
	fn.c = k * vec3_dot(ray.origin, ray.origin) - origin_y;
	if (solve_quadratic(fn, &intersection.from, &intersection.to))
	{
		if (intersections)
			if ((intersections->inner = malloc(1 * sizeof(struct s_intersection))))
			{
				intersections->len = 1;
				intersections->inner[0] = intersection;
			}
		n = vec3_unit(vec3_add(ray.origin, vec3_multv(ray.direction, intersection.from)));
		return ((struct s_hit) {
			.t = intersection.from,
			.normal = n,
			.u = 0.5 + atan2(n.z, n.x) / (2 * M_PI),
			.v = 0.5 - asin(n.y) / M_PI
		});
	}
	else
		return ((struct s_hit) { .t = -1.0 });
}

struct s_paraboloid	*read_paraboloid(t_toml_table *toml)
{
	struct s_paraboloid	*paraboloid;
	t_toml				*value;

	if (!(paraboloid = malloc(sizeof(*paraboloid))))
		return (rt_error(NULL, "Can not allocate paraboloid shape"));
	if (!read_shape_super(toml, &paraboloid->super))
		return (rt_error(paraboloid, "Invalid shape super in paraboloid shape"));
	if (!(value = table_get(toml, "radius")))
		return (rt_error(paraboloid, "Missing radius in paraboloid shape"));
	if (!read_digit(value, &paraboloid->r))
		return (rt_error(paraboloid, "Invalid radius in paraboloid shape"));
	if (!(value = table_get(toml, "height")))
		return (rt_error(paraboloid, "Missing height in paraboloid shape"));
	if (!read_digit(value, &paraboloid->h))
		return (rt_error(paraboloid, "Invalid height in paraboloid shape"));
	paraboloid->super.type = SHAPE_PARABOLOID;
	return (paraboloid);
}

void			free_paraboloid(struct s_paraboloid *paraboloid)
{
	free_shape_super(&paraboloid->super);
	free(paraboloid);
}