/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_material.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:12:44 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/09 16:22:10 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection_material.h"
#include <math.h>
#include "math/utils.h"
#include "raytrace.h"

static void						move_origin(
	t_vec3 *origin, t_vec3 direction, t_vec3 nm)
{
	double dot;

	dot = vec3_dot(direction, nm);
	nm = vec3_multv(nm, 1e-6);
	if (dot < 0)
		*origin = vec3_sub(*origin, nm);
	else
		*origin = vec3_add(*origin, nm);
}

static bool						move_direction(t_vec3 *direction, t_vec3 normal,
	double n, double cos_t)
{
	double	sin_t;
	double	sqrt_sin;

	sin_t = 1.0 - n * n * (1.0 - cos_t * cos_t);
	if (sin_t > 0)
	{
		sqrt_sin = sqrt(sin_t);
		*direction = (vec3_unit(vec3(
			(direction->x + cos_t * normal.x) * n - normal.x * sqrt_sin,
			(direction->y + cos_t * normal.y) * n - normal.y * sqrt_sin,
			(direction->z + cos_t * normal.z) * n - normal.z * sqrt_sin)));
		return (true);
	}
	else
		return (false);
}

t_color							refraction(t_scene *scene, struct s_ray ray,
	struct s_hit *hit)
{
	double			n;
	double			cos_t;
	t_vec3			tmp;

	ray.origin = ray_point_at(&ray, hit->t);
	tmp = ray.direction;
	cos_t = clamp(vec3_dot(ray.direction, hit->normal), -1.0, 1.0);
	if (cos_t < 0)
		cos_t *= -1.0;
	else
	{
		dswap(&ray.n1, &ray.n2);
		hit->normal = vec3_multv(hit->normal, -1.0);
	}
	n = ray.n1 / ray.n2;
	if (!move_direction(&ray.direction, hit->normal, n, cos_t))
		return (reflection(scene, ray, hit));
	move_origin(&ray.origin, tmp, hit->normal);
	return (raytrace(scene, ray, NULL));
}
