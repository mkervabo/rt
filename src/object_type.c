/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:05:35 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/19 14:21:10 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static bool	cone_revolution(t_cone *cone, t_ray *ray, t_hit_info *hit, float *t)
{
	t_vec3		v;

	v = vec3_add(ray->origin, vec3_multv(ray->direction, t[0]));
	if (cone->revolution == false && v.y > 0)
	{
		v = vec3_add(ray->origin, vec3_multv(ray->direction, t[1]));
		if (v.y > 0)
		{
			hit->t = -1.0;
			return (true);
		}
		else
			hit->t = t[1];
	}
	else
		hit->t = t[0];
	v.y = 0;
	v = vec3_unit(v);
	hit->n = vec3_unit((t_vec3) {
		.x = v.x / tan(cone->angle),
		.y = tan(cone->angle),
		.z = v.z / tan(cone->angle)
	});
	return (false);
}

t_hit_info	in_cone(t_cone *cone, t_ray *ray)
{
	t_polynome	poly;
	t_hit_info	hit;
	float		t[2];

	poly.a = ray->direction.y * ray->direction.y - cos(cone->angle)
		* cos(cone->angle);
	poly.b = 2 * (ray->direction.y * ray->origin.y - vec3_dot(ray->direction,
			ray->origin) * cos(cone->angle) * cos(cone->angle));
	poly.c = ray->origin.y * ray->origin.y - vec3_dot(ray->origin, ray->origin)
		* cos(cone->angle) * cos(cone->angle);
	if (solve_quadratic(poly, &t[0], &t[1]))
	{
		if (cone_revolution(cone, ray, &hit, t))
			return (hit);
	}
	else
		hit.t = -1.0;
	return (hit);
}

t_hit_info	in_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	t_polynome	poly;
	t_ray		r;
	t_hit_info	hit;

	r = *ray;
	r.direction.y = 0;
	r.origin.y = 0;
	poly.a = vec3_dot(r.direction, r.direction);
	poly.b = 2 * vec3_dot(r.origin, r.direction);
	poly.c = vec3_dot(r.origin, r.origin) - cylinder->r * cylinder->r;
	hit.t = solve_quadratic_min(poly);
	if (hit.t >= 0)
		hit.n = vec3_unit(vec3_add(r.origin, vec3_multv(r.direction, hit.t)));
	return (hit);
}

t_hit_info	in_sphere(t_sphere *sphere, t_ray *r)
{
	t_polynome	poly;
	t_hit_info	hit;

	poly.a = vec3_dot(r->direction, r->direction);
	poly.b = 2 * vec3_dot(r->origin, r->direction);
	poly.c = vec3_dot(r->origin, r->origin) - sphere->r * sphere->r;
	hit.t = solve_quadratic_min(poly);
	if (hit.t >= 0)
		hit.n = vec3_unit(vec3_add(r->origin, vec3_multv(r->direction, hit.t)));
	return (hit);
}

t_hit_info	in_plane(t_ray *ray)
{
	t_hit_info	hit;

	if (fabs(ray->direction.y) > 1e-6)
	{
		hit.t = -ray->origin.y / ray->direction.y;
		if (hit.t >= 0)
			hit.n = (t_vec3) {
				0, 1, 0
			};
	}
	else
		hit.t = -1.0;
	return (hit);
}
