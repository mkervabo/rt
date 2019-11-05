#include "triangle.h"
#include "shape_types.h"
#include "utils.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>

# define EPSILON 1e-12

struct s_hit hit_triangle(struct s_ray ray, struct s_triangle *triangle,
		struct s_intersection_tab *intersections)
{
	t_vec3 v0v1 = vec3_sub(triangle->v1, triangle->v0);
	t_vec3 v0v2 = vec3_sub(triangle->v2, triangle->v0);

	t_vec3 pvec = vec3_cross(ray.direction, v0v2);
	float det = vec3_dot(v0v1, pvec);

	if (fabs(det) < EPSILON)
		return ((struct s_hit) { .t = -1.0 });

	float invDet = 1 / det;

	t_vec3 tvec = vec3_sub(ray.origin, triangle->v0);

	float u = vec3_dot(tvec, pvec) * invDet;
	if (u < 0 || u > 1)
		return ((struct s_hit) { .t = -1.0 });

	t_vec3 qvec = vec3_cross(tvec, v0v1);
	float v = vec3_dot(ray.direction, qvec) * invDet;
	if (v < 0 || u + v > 1)
		return ((struct s_hit) { .t = -1.0 });

	float t = vec3_dot(v0v2, qvec) * invDet;
	if (intersections)
		if ((intersections->inner = malloc(1 * sizeof(struct s_intersection))))
		{
			intersections->len = 1;
			intersections->inner[0] = (struct s_intersection) {
				.from = t, .to = t };
		}
	return ((struct s_hit) {
		.t = t,
		.normal = vec3_unit(vec3_cross(v0v1, v0v2)),
		.u = u,
		.v = v
	});
}

struct s_triangle	*read_triangle(t_toml_table *toml)
{
	struct s_triangle	*triangle;
	t_toml				*value;

	if (!(triangle = malloc(sizeof(*triangle))))
		return (rt_error(NULL, "Can not allocate triangle"));
	if (!read_shape_super(toml, &triangle->super))
		return (rt_error(triangle, "Invalid super in triangle shape"));
	if (!read_toml_type(toml, &value, "v0", TOML_Table)
			|| !read_vec3(value->value.table_v, &triangle->v0))
		return (rt_error(triangle, "Invalid v0 in triangle shape"));
	if (!read_toml_type(toml, &value, "v1", TOML_Table)
			|| !read_vec3(value->value.table_v, &triangle->v1))
		return (rt_error(triangle, "Invalid v1 in triangle shape"));
	if (!read_toml_type(toml, &value, "v2", TOML_Table)
			|| !read_vec3(value->value.table_v, &triangle->v2))
		return (rt_error(triangle, "Invalid v3 in triangle shape"));
	triangle->super.type = SHAPE_TRIANGLE;
	return (triangle);
}

void			free_triangle(struct s_triangle *triangle)
{
	free_shape_super(&triangle->super);
	free(triangle);
}
