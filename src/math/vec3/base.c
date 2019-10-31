/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:37:37 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/09 21:01:18 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "math/vec3.h"

t_vec3	vec3(double x, double y, double z)
{
	return ((struct s_vec3) {
		.x = x,
		.y = y,
		.z = z
	});
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z));
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z));
}

t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	return (vec3(
		a.x * b.x,
		a.y * b.y,
		a.z * b.z));
}
