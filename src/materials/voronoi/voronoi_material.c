/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voronoi_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:11:18 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/09 16:33:27 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voronoi_material.h"
#include "../material_types.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/utils.h"
#include "config_utils.h"
#include <math.h>
#include <stdlib.h>

static double				smoothstep(double edge0, double edge1, double x)
{
	x = clamp((x - edge0) / (edge1 - edge0), 0, 1);
	return (x * x * (3 - 2 * x));
}

static void					noise(int i[], double k_va_wt[],
	double u, t_vec2 p_f[])
{
	t_vec2 g;
	t_vec3 o;
	t_vec2 r;
	double d;
	double w;

	g = vec2((double)i[0], (double)i[1]);
	o = vec3_mult(hash3(vec2_add(p_f[0], g)), vec3(u, u, 1.0));
	r = vec2_add(vec2_sub(g, p_f[1]), vec2(o.x, o.y));
	d = vec2_dot(r, r);
	w = pow(1.0 - smoothstep(0.0, 1.414, sqrt(d)), k_va_wt[0]);
	k_va_wt[1] += w * o.z;
	k_va_wt[2] += w;
}

double						voronoi(t_vec2 x, double u, double v)
{
	t_vec2	p_f[2];
	double	k_va_wt[3];
	int		i[2];

	p_f[0] = vec2(floor(x.x), floor(x.y));
	p_f[1] = vec2_sub(vec2(x.x, x.y), p_f[0]);
	k_va_wt[0] = 1.0 + 63.0 * pow(1.0 - v, 4.0);
	k_va_wt[1] = 0.0;
	k_va_wt[2] = 0.0;
	i[1] = -2;
	while (i[1] <= 2)
	{
		i[0] = -2;
		while (i[0] <= 2)
		{
			noise(i, k_va_wt, u, p_f);
			i[0]++;
		}
		i[1]++;
	}
	return (k_va_wt[1] / k_va_wt[2]);
}

t_color						voronoi_material_color(
	struct s_voronoi_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit)
{
	double	res;
	t_color color;

	res = voronoi(vec2(hit->u * material->size, hit->v * material->size),
		material->u, material->v);
	color = material_color(material->material, scene, ray, hit);
	return ((t_color) {
		.r = color.r * res,
		.g = color.g * res,
		.b = color.b * res
	});
}

struct s_voronoi_material	*read_voronoi_material(t_toml_table *toml)
{
	struct s_voronoi_material	*material;
	t_toml						*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate texture material"));
	if (!(value = table_get(toml, "size")))
		material->size = 50;
	else if (read_digit(value, &material->size) == false)
		return (rt_error(material, "Invalid size in voronoi material"));
	if (!(value = table_get(toml, "u")))
		material->u = 1;
	else if (read_digit(value, &material->u) == false || material->u < 0
		|| material->u > 1)
		return (rt_error(material, "Invalid u in voronoi material"));
	if (!(value = table_get(toml, "v")))
		material->v = 0;
	else if (read_digit(value, &material->v) == false || material->v < 0
		|| material->v > 1)
		return (rt_error(material, "Invalid v in voronoi material"));
	if (read_toml_type(toml, &value, "material", TOML_Table) == false)
		return (rt_error(material, "Missing material in voronoi material"));
	else if (!(material->material = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid material in voronoi material"));
	material->super.type = MATERIAL_VORONOI;
	return (material);
}
