/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:37:37 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/19 14:22:12 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3) {
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	});
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3) {
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	});
}

t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	return ((t_vec3) {
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z
	});
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
