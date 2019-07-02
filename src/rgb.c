/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:29:03 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/02 10:08:25 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color color_multv(t_color color, double v)
{
	return ((t_color) {
			.r = color.r * v,
			.g = color.g * v,
			.b = color.b * v,
		});
}

t_color color_sub(t_color a, t_color b)
{
	return ((t_color) {
			.r = a.r - b.r,
			.g = a.g - b.g,
			.b = a.b - b.b,
		});
}

uint8_t		clamp_rgb(double value)
{
	if (value < 0)
		return (0);
	if (value > 255)
		return (255);
	return (value);
}

uint32_t	to_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return (((uint32_t)r) << 16 | ((uint32_t)g) << 8 | b);
}
