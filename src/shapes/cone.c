/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:44:23 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/12 14:00:03 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include "shape_types.h"
#include "utils.h"
#include "math/quadratic.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>

static struct s_quadratic	calcul_quadratic(t_vec3 direction, t_vec3 origin,
						double angle)
{
	struct s_quadratic		fn;

	fn.a = direction.y * direction.y - cos(angle)
		* cos(angle);
	fn.b = 2 * (direction.y * origin.y - vec3_dot(direction,
		origin) * cos(angle) * cos(angle));
	fn.c = origin.y * origin.y - vec3_dot(origin, origin)
		* cos(angle) * cos(angle);
	return (fn);
}

static float				cone_revolution(t_vec3 *point,
						struct s_ray ray, struct s_intersection inter)
{
	*point = ray_point_at(&ray, inter.to);
	if (point->y > 0)
		return (-1.0);
	else
		return (inter.to);
}

static struct s_hit			cone_normal_and_uv(t_vec3 point, double angle,
							struct s_ray ray,
					float t)
{
	t_vec3	normal;

	point.y = 0;
	point = vec3_unit(point);
	normal = vec3_unit((t_vec3) {
		.x = point.x / tan(angle),
		.y = tan(angle),
		.z = point.z / tan(angle)
	});
	return ((struct s_hit) {
		.t = t,
		.normal = normal,
		.u = 0.5 + atan2(normal.z, normal.x) / (2 * M_PI),
		.v = ray.direction.y * t + ray.origin.y
	});
}

struct s_hit				hit_cone(struct s_ray ray, struct s_cone *cone,
							struct s_intersection_tab *intersections)
{
	struct s_quadratic		fn;
	struct s_intersection	intersection;
	t_vec3					point;
	float					t;

	fn = calcul_quadratic(ray.direction, ray.origin, cone->angle);
	if (solve_quadratic(fn, &intersection.from, &intersection.to))
	{
		if (intersections)
			if ((intersections->inner = malloc(1
			* sizeof(struct s_intersection))))
			{
				intersections->len = 1;
				intersections->inner[0] = intersection;
			}
		t = intersection.from >= 0 ? intersection.from : intersection.to;
		point = ray_point_at(&ray, t);
		if (!cone->revolution && point.y > 0)
			t = cone_revolution(&point, ray, intersection);
		return (cone_normal_and_uv(point, cone->angle, ray, t));
	}
	else
		return ((struct s_hit) { .t = -1.0 });
}

struct s_cone				*read_cone(t_toml_table *toml)
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
