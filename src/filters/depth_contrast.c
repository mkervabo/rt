/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_contrast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:19:48 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 17:21:48 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/size.h"
#include "color.h"
#include <stdint.h>
#include <stddef.h>
#include "filter_types.h"
#include "depth_contrast.h"
#include "config_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "toml.h"
#include <math.h>

static void						get_min_max_depth(double *min, double *max,
								struct s_size w, struct s_pixel_hit *hits)
{
	ssize_t		i;

	*min = INFINITY;
	*max = -INFINITY;
	i = 0;
	while (i < w.width * w.height)
	{
		if (hits[i].t >= 0)
		{
			*min = hits[i].t < *min ? hits[i].t : *min;
			*max = hits[i].t > *max ? hits[i].t : *max;
		}
		i++;
	}
}

void							depth_contrast_filter(
								struct s_depth_contrast_filter *d,
								uint32_t *pixels,
								struct s_pixel_hit *hits,
								struct s_size window)
{
	double		max;
	double		min;
	size_t		i;
	t_color		color;

	(void)d;
	get_min_max_depth(&min, &max, window, hits);
	i = 0;
	while (i < window.width * window.height)
	{
		if (hits[i].t < 0)
			pixels[i] = 0;
		else if (max == min)
			pixels[i] = 0xFFFF00;
		else
		{
			color.r = 255 - ((hits[i].t - min) / (max - min)) * 255;
			color.g = color.r;
			color.b = color.r;
			pixels[i] = color_to_rgb(color);
		}
		i++;
	}
}

struct s_depth_contrast_filter	*read_depth_contrast_filter(t_toml_table *toml)
{
	struct s_depth_contrast_filter	*depth_contrast;

	(void)toml;
	if (!(depth_contrast = malloc(sizeof(*depth_contrast))))
		return (rt_error(NULL, "Can not allocate depth_contrast filter"));
	depth_contrast->super.type = FILTER_DEPTH_CONTRAST;
	return (depth_contrast);
}

void							free_depth_contrast_filter(
	struct s_depth_contrast_filter *filter)
{
	free(filter);
}
