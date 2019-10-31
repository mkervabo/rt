/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:18:54 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/09 21:01:10 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "math/vec2.h"

t_vec2	vec2(double x, double y)
{
	return ((struct s_vec2) {
		.x = x,
		.y = y
	});
}

t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	return (vec2(
		a.x + b.x,
		a.y + b.y));
}

t_vec2	vec2_sub(t_vec2 a, t_vec2 b)
{
	return (vec2(
		a.x - b.x,
		a.y - b.y));
}

t_vec2	vec2_mult(t_vec2 a, t_vec2 b)
{
	return (vec2(
		a.x * b.x,
		a.y * b.y));
}
