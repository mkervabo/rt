/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:47:30 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/20 14:58:33 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/vec3.h"
#include <math.h>

static t_vec3	vec3_rotate_x(t_vec3 v, double angle)
{
	const double cos_a = cos(angle);
	const double sin_a = sin(angle);

	return (vec3(
		v.x,
		v.y * cos_a - v.z * sin_a,
		v.y * sin_a + v.z * cos_a
	));
}

static t_vec3	vec3_rotate_y(t_vec3 v, double angle)
{
	const double cos_a = cos(angle);
	const double sin_a = sin(angle);

	return (vec3(
		v.x * cos_a + v.z * sin_a,
		v.y,
		-v.x * sin_a + v.z * cos_a
	));
}

static t_vec3	vec3_rotate_z(t_vec3 v, double angle)
{
	const double cos_a = cos(angle);
	const double sin_a = sin(angle);

	return (vec3(
		v.x * cos_a - v.y * sin_a,
		v.x * sin_a + v.y * cos_a,
		v.z
	));
}

t_vec3			vec3_rotate(t_vec3 v, t_vec3 rot)
{
	v = vec3_rotate_x(v, rot.x);
	v = vec3_rotate_y(v, rot.y);
	v = vec3_rotate_z(v, rot.z);
	return (v);
}
