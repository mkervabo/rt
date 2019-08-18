/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:04:32 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/08/18 17:22:55 by dde-jesu         ###   ########.fr       */
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
		struct s_intersection **intersections)
{
	struct s_quadratic		fn;
	struct s_intersection	intersection;
	t_vec3					n;

	fn.a = vec3_dot(ray.direction, ray.direction);
	fn.b = 2 * vec3_dot(ray.origin, ray.direction);
	fn.c = vec3_dot(ray.origin, ray.origin) - sphere->r * sphere->r;
	if (solve_quadratic(fn, &intersection.from, &intersection.to))
	{
		/*TODO: if (intersections)
			*intersection = &intersection;*/
		n = vec3_unit(vec3_add(ray.origin, vec3_multv(ray.direction, intersection.from)));
		return ((struct s_hit) {
			.t = intersection.from,
			.normal = n,
			.u = 0.5 + atan2(n.z, n.x) / (2 * M_PI),
			.v = fmod(n.y, 1)
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
		return (NULL);
	if (!(radius = table_get(toml, "radius")))
		return (nfree(sphere));
	if (!read_shape_super(toml, &sphere->super))
		return (nfree(sphere));
	if (read_digit(radius, &sphere->r) == false)
		return (nfree(sphere));
	sphere->super.type = SHAPE_SPHERE;
	return (sphere);
}
