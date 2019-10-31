/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:22:20 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/12 14:27:01 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"
#include "shape_types.h"
#include "utils.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-12

static struct s_hit		wait_name(float invdet, t_vec3 v0v[2],
	t_vec3 vec[2], struct s_ray ray)
{
	float	u;
	t_vec3	qvec;
	float	v;
	float	t;

	u = vec3_dot(vec[1], vec[0]) * invdet;
	if (u < 0 || u > 1)
		return ((struct s_hit) { .t = -1.0 });
	qvec = vec3_cross(vec[1], v0v[0]);
	v = vec3_dot(ray.direction, qvec) * invdet;
	if (v < 0 || u + v > 1)
		return ((struct s_hit) { .t = -1.0 });
	t = vec3_dot(v0v[1], qvec) * invdet;
	return ((struct s_hit) {
		.t = t,
		.normal = vec3_unit(vec3_cross(v0v[0], v0v[1])),
		.u = u,
		.v = v
	});
}

struct s_hit			hit_triangle(struct s_ray ray,
	struct s_triangle *triangle, struct s_intersection_tab *intersections)
{
	t_vec3			v0v[2];
	t_vec3			vec[2];
	float			det;
	float			invdet;
	struct s_hit	t;

	v0v[0] = vec3_sub(triangle->v1, triangle->v0);
	v0v[1] = vec3_sub(triangle->v2, triangle->v0);
	vec[0] = vec3_cross(ray.direction, v0v[1]);
	det = vec3_dot(v0v[0], vec[0]);
	if (fabs(det) < EPSILON)
		return ((struct s_hit) { .t = -1.0 });
	invdet = 1 / det;
	vec[1] = vec3_sub(ray.origin, triangle->v0);
	t = wait_name(invdet, v0v, vec, ray);
	if (intersections)
		if ((intersections->inner = malloc(1 * sizeof(struct s_intersection))))
		{
			intersections->len = 1;
			intersections->inner[0] = (struct s_intersection) {
				.from = t.t, .to = t.t };
		}
	return (t);
}

struct s_triangle		*read_triangle(t_toml_table *toml)
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

void					free_triangle(struct s_triangle *triangle)
{
	free_shape_super(&triangle->super);
	free(triangle);
}
