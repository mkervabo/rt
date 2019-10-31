/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:05:56 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 17:20:52 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/size.h"
#include "color.h"
#include <stdint.h>
#include <stddef.h>
#include "filter_types.h"
#include "blur.h"
#include "config_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "toml.h"

static t_color			blend(uint16_t rgb[3], size_t j, uint32_t tmp[9])
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

static t_color			merge_color_around(uint32_t *pixels, size_t i,
						struct s_size window)
{
	uint32_t	tmp[25];
	size_t		j;
	ssize_t		coord[3];
	uint16_t	rgb[3];

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	j = 0;
	coord[1] = -2;
	while (coord[1] <= 2)
	{
		coord[0] = -2;
		while (coord[0] <= 2)
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

void					blur_filter(struct s_blur_filter *blur,
						uint32_t *pixels, struct s_pixel_hit *hits,
						struct s_size window)
{
	size_t			i;
	size_t			j;

	(void)hits;
	j = 0;
	while (j < blur->size)
	{
		i = 0;
		while (i < window.width * window.height)
		{
			pixels[i] = color_to_rgb(merge_color_around(pixels, i, window));
			i++;
		}
		j++;
	}
}

struct s_blur_filter	*read_blur_filter(t_toml_table *toml)
{
	struct s_blur_filter	*blur;
	t_toml					*value;

	if (!(blur = malloc(sizeof(*blur))))
		return (rt_error(NULL, "Can not allocate blur filter"));
	if (!(value = table_get(toml, "size")))
		blur->size = 1;
	else if (!read_digit(value, &blur->size))
		return (rt_error(blur, "Invalid blur filter"));
	blur->super.type = FILTER_BLUR;
	return (blur);
}

void					free_blur_filter(struct s_blur_filter *filter)
{
	free(filter);
}
