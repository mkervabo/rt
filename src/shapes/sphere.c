/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:04:32 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/10/19 14:17:22 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "shape_types.h"
#include "utils.h"
#include "math/quadratic.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>

struct s_hit hit_sphere(struct s_ray ray, struct s_sphere *sphere,
		struct s_intersection_tab *intersections)
{
	struct s_quadratic		fn;
	struct s_intersection	intersection;
	t_vec3					n;
	float					t;

	fn.a = vec3_dot(ray.direction, ray.direction);
	fn.b = 2 * vec3_dot(ray.origin, ray.direction);
	fn.c = vec3_dot(ray.origin, ray.origin) - sphere->r * sphere->r;
	if (solve_quadratic(fn, &intersection.from, &intersection.to))
	{
		if (intersections)
			if ((intersections->inner = malloc(1 * sizeof(struct s_intersection)))) {
				intersections->len = 1;
				intersections->inner[0] = intersection;
			}
		t = intersection.from >= 0 ? intersection.from : intersection.to;
		n = vec3_unit(vec3_add(ray.origin, vec3_multv(ray.direction, t)));
		return ((struct s_hit) {
			.t = t,
			.normal = n,
			.u = 0.5 + atan2(n.z, n.x) / (2 * M_PI),
			.v = 0.5 - asin(n.y) / M_PI
		});
	}
	else
		return ((struct s_hit) {
			.t = -1.0
		});
}

struct s_sphere	*read_sphere(t_toml_table *toml)
{
	struct s_sphere	*sphere;
	t_toml			*radius;

	if (!(sphere = malloc(sizeof(*sphere))))
		return (rt_error(NULL, "Can not allocate sphere shape"));
	if (!(radius = table_get(toml, "radius")))
		return (rt_error(sphere, "Misssing radius in sphere shape"));
	if (!read_shape_super(toml, &sphere->super))
		return (rt_error(sphere, "invalid super in sphere shape"));
	if (read_digit(radius, &sphere->r) == false)
		return (rt_error(sphere, "Invalide radius in sphere shape"));
	sphere->super.type = SHAPE_SPHERE;
	return (sphere);
}
