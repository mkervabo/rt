/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_v.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 14:30:35 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/19 14:22:09 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	vec3_multv(t_vec3 a, double v)
{
	return ((t_vec3) {
		.x = a.x * v,
		.y = a.y * v,
		.z = a.z * v
	});
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
	return (vec3_divv(v, vec3_length(v)));
}
