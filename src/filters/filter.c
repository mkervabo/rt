/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:25:15 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 16:14:42 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filter.h"
#include "filter_types.h"

#include "config.h"
#include "config_utils.h"
#include "string_utils.h"
#include <stdlib.h>

#include "black_and_white.h"
#include "sepia.h"
#include "negative.h"
#include "anti_aliasing.h"
#include "cartoon.h"
#include "blur.h"
#include "depth_contrast.h"
#include "motion_blur.h"

void			apply_filter(t_filter *filter, uint32_t *pixels,
				struct s_pixel_hit *hits, struct s_size window)
{
	if (filter->type == FILTER_BLACK_AND_WHITE)
		black_and_white_filter(pixels, hits, window);
	else if (filter->type == FILTER_SEPIA)
		sepia_filter(pixels, hits, window);
	else if (filter->type == FILTER_NEGATIVE)
		negative_filter(pixels, hits, window);
	else if (filter->type == FILTER_ANTI_ALIASING)
		anti_aliasing_filter((struct s_anti_aliasing_filter *)filter, pixels,
			hits, window);
	else if (filter->type == FILTER_CARTOON)
		cartoon_filter((struct s_cartoon_filter *)filter, pixels, hits, window);
	else if (filter->type == FILTER_BLUR)
		blur_filter((struct s_blur_filter *)filter, pixels, hits, window);
	else if (filter->type == FILTER_DEPTH_CONTRAST)
		depth_contrast_filter((struct s_depth_contrast_filter *)filter, pixels,
			hits, window);
}

void			apply_video_filter(t_filter *filter, uint32_t **pixels,
	size_t *nframes, struct s_size window)
{
	if (filter->type == FILTER_MOTION_BLUR)
		motion_blur_video_filter((struct s_motion_blur_filter *)filter, pixels,
		nframes, window);
}

t_filter		*read_filter(t_toml_table *toml)
{
	t_toml	*type;

	if (!(type = table_get(toml, "type")))
		return (NULL);
	if (type->type != TOML_String)
		return (NULL);
	if (ft_strcmp(type->value.string_v, "BLACK_AND_WHITE") == 0)
		return ((t_filter *)read_black_and_white_filter(toml));
	else if (ft_strcmp(type->value.string_v, "SEPIA") == 0)
		return ((t_filter *)read_sepia_filter(toml));
	else if (ft_strcmp(type->value.string_v, "NEGATIVE") == 0)
		return ((t_filter *)read_negative_filter(toml));
	else if (ft_strcmp(type->value.string_v, "ANTI_ALIASING") == 0)
		return ((t_filter *)read_anti_aliasing_filter(toml));
	else if (ft_strcmp(type->value.string_v, "CARTOON") == 0)
		return ((t_filter *)read_cartoon_filter(toml));
	else if (ft_strcmp(type->value.string_v, "BLUR") == 0)
		return ((t_filter *)read_blur_filter(toml));
	else if (ft_strcmp(type->value.string_v, "DEPTH_CONTRAST") == 0)
		return ((t_filter *)read_depth_contrast_filter(toml));
	else if (ft_strcmp(type->value.string_v, "MOTION_BLUR") == 0)
		return ((t_filter *)read_motion_blur_filter(toml));
	return (NULL);
}

t_filter		**read_filters(t_toml_table *toml, size_t *size)
{
	t_toml		*value;
	t_filter	**filters;
	size_t		i;

	if (!read_toml_type(toml, &value, "filters", TOML_Array))
		*size = 0;
	else
		*size = value->value.array_v->len;
	if (*size > 0 && value->value.array_v->inner[0].type != TOML_Table)
		return (NULL);
	if (!(filters = malloc(sizeof(*filters) * *size)))
		return (NULL);
	i = 0;
	while (i < *size)
	{
		if (!(filters[i] =
		read_filter(value->value.array_v->inner[i].value.table_v)))
			return ((*size = 0) + free_filter_array(filters, i));
		i++;
	}
	return (filters);
}

void			free_filter(t_filter *filter)
{
	if (filter->type == FILTER_BLACK_AND_WHITE)
		free_black_and_white_filter((struct s_black_and_white_filter *)filter);
	else if (filter->type == FILTER_SEPIA)
		free_sepia_filter((struct s_sepia_filter *)filter);
	else if (filter->type == FILTER_NEGATIVE)
		free_negative_filter((struct s_negative_filter *)filter);
	else if (filter->type == FILTER_ANTI_ALIASING)
		free_anti_aliasing_filter((struct s_anti_aliasing_filter *)filter);
	else if (filter->type == FILTER_CARTOON)
		free_cartoon_filter((struct s_cartoon_filter *)filter);
	else if (filter->type == FILTER_BLUR)
		free_blur_filter((struct s_blur_filter *)filter);
	else if (filter->type == FILTER_DEPTH_CONTRAST)
		free_depth_contrast_filter((struct s_depth_contrast_filter *)filter);
}
