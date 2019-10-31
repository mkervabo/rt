/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:36:00 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 17:24:21 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/size.h"
#include "color.h"
#include <stdint.h>
#include <stddef.h>
#include "filter_types.h"
#include "anti_aliasing.h"
#include "config_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "toml.h"

static t_color					blend(uint16_t rgb[3], size_t j,
								uint32_t tmp[9])
{
	size_t		i;
	t_color		color;
	t_color		final;

	i = 0;
	while (i < j)
	{
		color = color_from_rgb(tmp[i]);
		rgb[0] += color.r;
		rgb[1] += color.g;
		rgb[2] += color.b;
		i++;
	}
	final.r = rgb[0] / j;
	final.g = rgb[1] / j;
	final.b = rgb[2] / j;
	return (final);
}

static t_color					merge_color_around(uint32_t *pixels, size_t i,
								struct s_size window)
{
	uint32_t	tmp[9];
	size_t		j;
	ssize_t		coord[3];
	uint16_t	rgb[3];

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	j = 0;
	coord[1] = -1;
	while (coord[1] <= 1)
	{
		coord[0] = -1;
		while (coord[0] <= 1)
		{
			coord[2] = (ssize_t)i + coord[1] * window.width + coord[0];
			if (coord[2] >= 0 && coord[2] < window.width * window.height)
				tmp[j++] = pixels[(size_t)coord[2]];
			coord[0]++;
		}
		coord[1]++;
	}
	return (blend(rgb, j, tmp));
}

void							anti_aliasing_filter(
								struct s_anti_aliasing_filter *aa,
								uint32_t *pixels,
								struct s_pixel_hit *hits,
								struct s_size window)
{
	size_t			i;
	size_t			j;

	j = 0;
	while (j < aa->size)
	{
		i = 0;
		while (i < window.width * window.height)
		{
			if (i + window.width + 2 < window.width * window.height
			&& ((hits[i].t != hits[i + 2].t && hits[i].who != hits[i + 2].who)
			|| (hits[i].t != hits[i + window.width].t && hits[i].who != hits[i
			+ window.width].who) || (hits[i].t != hits[i + window.width + 2].t
			&& hits[i].who != hits[i + window.width + 2].who)))
				pixels[i] = color_to_rgb(merge_color_around(pixels, i, window));
			i++;
		}
		j++;
	}
}

struct s_anti_aliasing_filter	*read_anti_aliasing_filter(t_toml_table *toml)
{
	struct s_anti_aliasing_filter	*anti_aliasing;
	t_toml							*value;

	if (!(anti_aliasing = malloc(sizeof(*anti_aliasing))))
		return (rt_error(NULL, "Can not allocate anti aliasing filter"));
	if (!(value = table_get(toml, "size")))
		anti_aliasing->size = 1;
	else if (!read_digit(value, &anti_aliasing->size))
		return (rt_error(anti_aliasing, "Invalid anti aliasing filter"));
	anti_aliasing->super.type = FILTER_ANTI_ALIASING;
	return (anti_aliasing);
}

void							free_anti_aliasing_filter(
	struct s_anti_aliasing_filter *filter)
{
	free(filter);
}
