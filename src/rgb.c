/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:29:03 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/19 14:21:59 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
