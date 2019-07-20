/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_v.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 14:30:35 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/20 14:57:12 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug/assert.h"
#include "math/vec3.h"

t_vec3	vec3_multv(t_vec3 a, double v)
{
	return (vec3(
		a.x * v,
		a.y * v,
		a.z * v
	));
}

t_vec3	vec3_divv(t_vec3 a, double v)
{
	return ((t_vec3) {
		.x = a.x / v,
		.y = a.y / v,
		.z = a.z / v
	});
}

t_vec3	vec3_unit(t_vec3 v)
{
	double	length;
	
	length = vec3_length(v);
	assertf(length != 0, "Unit vector length is not 0");
	return (vec3_divv(v, length));
}
