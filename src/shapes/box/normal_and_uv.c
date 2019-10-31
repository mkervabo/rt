/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_and_uv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 20:45:14 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/10 16:59:23 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "box.h"
#include "../shape_types.h"
#include "../utils.h"
#include "math/vec3.h"
#include "config_utils.h"
#include <math.h>
#include <stdio.h>

static bool		double_cmp(double a, double b, double coef)
{
	return (fabs(a - b) < coef);
}

static t_vec3	box_normal(t_vec3 p, t_vec3 a, t_vec3 b)
{
	double	coef;

	coef = 1e-6;
	while (true)
	{
		if (double_cmp(p.x, a.x, coef))
			return (vec3(-1, 0, 0));
		else if (double_cmp(p.x, b.x, coef))
			return (vec3(1, 0, 0));
		else if (double_cmp(p.y, a.y, coef))
			return (vec3(0, -1, 0));
		else if (double_cmp(p.y, b.y, coef))
			return (vec3(0, 1, 0));
		else if (double_cmp(p.z, a.z, coef))
			return (vec3(0, 0, -1));
		else if (double_cmp(p.z, b.z, coef))
			return (vec3(0, 0, 1));
		coef *= 10;
	}
}

static void		box_uvs(double *u, double *v, t_vec3 normal, t_vec3 dir)
{
	if (normal.x != 0)
	{
		*u = 0.5 - (dir.z / (2 * dir.x));
		*v = 0.5 - (dir.y / (2 * dir.x)) * (normal.x > 0 ? 1 : -1);
	}
	else if (normal.y != 0)
	{
		*u = 0.5 + (dir.x / (2 * dir.y)) * (normal.y > 0 ? 1 : -1);
		*v = 0.5 + (dir.z / (2 * dir.y));
	}
	else if (normal.z != 0)
	{
		*u = 0.5 + (dir.x / (2 * dir.z));
		*v = 0.5 - (dir.y / (2 * dir.z)) * (normal.z > 0 ? 1 : -1);
	}
}

struct s_hit	box_normal_and_uv(double min, struct s_ray *ray,
	struct s_box *box)
{
	t_vec3	normal;
	double	u;
	double	v;
	t_vec3	p;

	p = ray_point_at(ray, min);
	normal = box_normal(p, box->bounds[0], box->bounds[1]);
	box_uvs(&u, &v, normal, vec3_unit(p));
	return ((struct s_hit) {
		.t = min,
		.normal = normal,
		.u = u,
		.v = v
	});
}
