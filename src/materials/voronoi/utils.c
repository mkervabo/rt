/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:25:02 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 17:39:18 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include "voronoi_material.h"
#include "math/vec2.h"
#include "math/vec3.h"

t_vec3				hash3(t_vec2 p)
{
	t_vec3 q;
	t_vec3 f;

	q = vec3(
		vec2_dot(p, vec2(127.1, 311.7)),
		vec2_dot(p, vec2(269.5, 183.3)),
		vec2_dot(p, vec2(419.2, 371.9)));
	q = vec3_multv(vec3(sin(q.x), sin(q.y), sin(q.z)), 43758.5453);
	f = vec3(floor(q.x), floor(q.y), floor(q.z));
	return (vec3_sub(q, f));
}

void				free_voronoi_material(
	struct s_voronoi_material *material)
{
	free_material(material->material);
	free(material);
}

double				voronoi_material_transparency(
	struct s_voronoi_material *material,
	struct s_hit *hit, t_material **color)
{
	return (material_transparency(material->material, hit, color));
}
