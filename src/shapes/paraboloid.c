/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:14:47 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/12 14:00:33 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paraboloid.h"
#include "shape_types.h"
#include "utils.h"
#include "math/quadratic.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>

static struct s_hit			hit_return(struct s_intersection intersection,
							t_vec3 n)
{
	return ((struct s_hit) {
		.t = intersection.from,
		.normal = n,
		.u = 0.5 + atan2(n.z, n.x) / (2 * M_PI),
		.v = 0.5 - asin(n.y) / M_PI
	});
}

static struct s_quadratic	calcul_quadratic(struct s_ray ray, double k,
							double y[2])
{
	struct s_quadratic		fn;

	fn.a = k * vec3_dot(ray.direction, ray.direction);
	fn.b = 2 * k * vec3_dot(ray.origin, ray.direction) - y[0];
	fn.c = k * vec3_dot(ray.origin, ray.origin) - y[1];
	return (fn);
}

static void					init_v(struct s_ray *ray, double y[2])
{
	y[0] = ray->direction.y;
	y[1] = ray->direction.y;
	ray->direction.y = 0;
	ray->origin.y = 0;
}

struct s_hit				hit_paraboloid(struct s_ray ray,
							struct s_paraboloid *paraboloid,
							struct s_intersection_tab *intersections)
{
	struct s_quadratic		fn;
	struct s_intersection	intersection;
	t_vec3					n;
	double					k;
	double					y[2];

	if (paraboloid->r == 0)
		return ((struct s_hit) { .t = -1.0 });
	init_v(&ray, y);
	k = paraboloid->h / (paraboloid->r * paraboloid->r);
	fn = calcul_quadratic(ray, k, y);
	if (solve_quadratic(fn, &intersection.from, &intersection.to))
	{
		if (intersections)
			if ((intersections->inner = malloc(1 * sizeof(intersection))))
			{
				intersections->len = 1;
				intersections->inner[0] = intersection;
			}
		n = vec3_unit(vec3_add(ray.origin, vec3_multv(ray.direction,
		intersection.from)));
		return (hit_return(intersection, n));
	}
	else
		return ((struct s_hit) { .t = -1.0 });
}

struct s_paraboloid			*read_paraboloid(t_toml_table *toml)
{
	struct s_paraboloid	*paraboloid;
	t_toml				*value;

	if (!(paraboloid = malloc(sizeof(*paraboloid))))
		return (rt_error(NULL, "Can not allocate paraboloid shape"));
	if (!read_shape_super(toml, &paraboloid->super))
		return (rt_error(paraboloid, "Invalid super in paraboloid shape"));
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
