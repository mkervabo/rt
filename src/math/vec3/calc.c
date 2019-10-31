/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:55:08 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/11/05 13:21:39 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/vec3.h"
#include <math.h>

double	vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_invert(t_vec3 v)
{
	return (vec3(
		1 / v.x,
		1 / v.y,
		1 / v.z));
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return (vec3(
		(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z),
		(a.x * b.y) - (a.y * b.x)));
}

bool	vec3_is_zero(t_vec3 v)
{
	return (v.x == 0 && v.y == 0 && v.z == 0);
}
