/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:05:00 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/12 11:38:03 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.h"
#include "video.h"
#include "object.h"
#include "material.h"
#include <math.h>
#include "config_utils.h"
#include <stdlib.h>

static bool		read_frame_position(struct s_frame *frame, t_toml_table *toml)
{
	t_toml	*value;

	if (read_toml_type(toml, &value, "position", TOML_Table))
	{
		if (!read_vec3(value->value.table_v, &frame->position))
			return (false);
	}
	else
		frame->position = vec3(0, 0, 0);
	if (read_toml_type(toml, &value, "rotation", TOML_Table))
	{
		if (!read_vec3(value->value.table_v, &frame->rotation))
			return (false);
		frame->rotation = vec3_multv(frame->rotation, M_PI / 180);
	}
	else
		frame->rotation = vec3(0, 0, 0);
	return (true);
}

bool			read_frame(struct s_frame *frame, t_toml_table *toml)
{
	t_toml	*f;
	t_toml	*value;

	if (!(read_toml_type(toml, &f, "seconde", TOML_Table)))
		return (false);
	if (!(value = table_get(f->value.table_v, "from")))
		return (false);
	else if (read_digit(value, &frame->from) == false)
		return (false);
	if (!(value = table_get(f->value.table_v, "to")))
		return (false);
	else if (read_digit(value, &frame->to) == false)
		return (false);
	if (read_frame_position(frame, toml) == false)
		return (false);
	return (true);
}

bool			read_video_shape(t_toml_table *toml,
	struct s_video_shape *video)
{
	t_toml			*frame;
	size_t			i;

	if (read_toml_type(toml, &frame, "video", TOML_Array) == false)
		return (false);
	if (frame->value.array_v->len == 0
		|| frame->value.array_v->inner[0].type != TOML_Table)
		return (false);
	video->video_len = frame->value.array_v->len;
	if (!(video->video = malloc(sizeof(struct s_frame) * video->video_len)))
		return (false);
	i = 0;
	while (i < video->video_len)
	{
		if (!read_frame(video->video + i,
			frame->value.array_v->inner[i].value.table_v))
			return ((bool)rt_error(video->video, "Invalid video frame"));
		i++;
	}
	return (true);
}

static bool		read_video_second_light(struct s_video_light *video,
	t_toml *video_frame, size_t i)
{
	t_toml			*second;

	if (!(second = table_get(video_frame->value.array_v->inner[i].value.table_v,
		"second")))
		return ((bool)rt_error(video->frame,
		"Missing second in light video frame"));
	else if (read_digit(second, &video->frame[i].second) == false)
	{
		return ((bool)rt_error(video->frame,
			"Invalid second in light video frame"));
	}
	if (!(video->frame[i].light = read_light(
		video_frame->value.array_v->inner[i].value.table_v)))
		return ((bool)rt_error(video->frame,
		"Invalid light in light video frame"));
	else
		video->frame[i].light->video = *video;
	return (true);
}

bool			read_video_light(t_toml_table *toml,
	struct s_video_light *video)
{
	t_toml			*video_frame;
	size_t			i;

	if (read_toml_type(toml, &video_frame, "video_frame", TOML_Array) == false)
		return (false);
	if (video_frame->value.array_v->len == 0
		|| video_frame->value.array_v->inner[0].type != TOML_Table)
		return (false);
	video->frame_len = video_frame->value.array_v->len;
	if (!(video->frame = malloc(sizeof(struct s_video_frame)
		* video->frame_len)))
		return (false);
	i = 0;
	while (i < video->frame_len)
	{
		if (read_video_second_light(video, video_frame, i) == false)
			return (false);
		i++;
	}
	return (true);
}
