/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:19:06 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/12 13:59:29 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "sphere.h"
#include "shape_types.h"
#include "utils.h"
#include "math/quadratic.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>

struct s_hit		hit_cylinder(struct s_ray ray, struct s_cylinder *cylinder,
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
		hit.v = r.direction.y * hit.t + r.origin.y;
	return (hit);
}

struct s_cylinder	*read_cylinder(t_toml_table *toml)
{
	struct s_cylinder	*cylinder;
	t_toml				*radius;

	if (!(cylinder = malloc(sizeof(*cylinder))))
		return (rt_error(NULL, "Can not allocate cylinder shape"));
	if (!(radius = table_get(toml, "radius")))
		return (rt_error(cylinder, "Missing radius in cylinder shape"));
	if (!read_shape_super(toml, &cylinder->super))
		return (rt_error(cylinder, "Invalid super in cylinder shape"));
	if (read_digit(radius, &cylinder->r) == false)
		return (rt_error(cylinder, "Invalid radius in cylinder shape"));
	cylinder->super.type = SHAPE_CYLINDER;
	return (cylinder);
}

void				free_cylinder(struct s_cylinder *cylinder)
{
	free_shape_super(&cylinder->super);
	free(cylinder);
}
