#include "cone.h"
#include "shape_types.h"
#include "utils.h"
#include "math/quadratic.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>

struct s_hit hit_cone(struct s_ray ray, struct s_cone *cone,
		struct s_intersection_tab *intersections)
{
	struct s_quadratic		fn;
	struct s_intersection	intersection;
	t_vec3					p;
	t_vec3					n;
	float					t;

	fn.a = ray.direction.y * ray.direction.y - cos(cone->angle)
		* cos(cone->angle);
	fn.b = 2 * (ray.direction.y * ray.origin.y - vec3_dot(ray.direction,
		ray.origin) * cos(cone->angle) * cos(cone->angle));
	fn.c = ray.origin.y * ray.origin.y - vec3_dot(ray.origin, ray.origin)
		* cos(cone->angle) * cos(cone->angle);
	if (solve_quadratic(fn, &intersection.from, &intersection.to))
	{
		// TODO: if revolution = true remove invalid points from intersections
		if (intersections)
			if ((intersections->inner = malloc(1 * sizeof(struct s_intersection)))) {
				intersections->len = 1;
				intersections->inner[0] = intersection;
			}
		t = intersection.from >= 0 ? intersection.from : intersection.to;
		p = ray_point_at(&ray, t);
		if (!cone->revolution && p.y > 0) {
			p = ray_point_at(&ray, intersection.to);
			if (p.y > 0)
				return ((struct s_hit) { .t = -1.0 });
			else
				t = intersection.to;
		}
		p.y = 0;
		p = vec3_unit(p);
		n  = vec3_unit((t_vec3) {
			.x = p.x / tan(cone->angle),
			.y = tan(cone->angle),
			.z = p.z / tan(cone->angle)
		});
		return ((struct s_hit) {
			.t = t,
			.normal = n,
			.u = 0.5 + atan2(n.z, n.x) / (2 * M_PI),
			.v = ray.direction.y * t + ray.origin.y
		});
	}
	else
		return ((struct s_hit) { .t = -1.0 });
}

struct s_cone	*read_cone(t_toml_table *toml)
{
	struct s_cone	*cone;
	t_toml			*value;

	if (!(cone = malloc(sizeof(*cone))))
		return (rt_error(NULL, "Can not allocate cone shape"));
	if (!read_shape_super(toml, &cone->super))
		return (rt_error(cone, "invalid super in cone shape"));
	if (!(value = table_get(toml, "angle")))
		return (rt_error(cone, "Misssing angle in cone shape"));
	if (!read_digit(value, &cone->angle))
		return (rt_error(cone, "Invalide angle in cone shape"));
	if (!read_toml_type(toml, &value, "revolution", TOML_Boolean))
		cone->revolution = false;
	else
		cone->revolution = value->value.boolean_v;
	cone->angle *= M_PI / 180;
	cone->super.type = SHAPE_CONE;
	return (cone);
}

void			free_cone(struct s_cone *cone)
{
	free_shape_super(&cone->super);
	free(cone);
}