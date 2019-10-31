/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:13:11 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/12 11:36:04 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.h"
#include "video.h"
#include "object.h"
#include "config_utils.h"
#include <stdlib.h>

static bool		read_video_second(struct s_video_shape *video,
	t_toml *video_frame, size_t i)
{
	t_toml			*second;
	t_toml			*material;

	if (!(second = table_get(video_frame->value.array_v->inner[i].value.table_v,
		"second")))
		return ((bool)rt_error(video->frame, "Missing second in video frame"));
	else if (read_digit(second, &video->frame[i].second) == false)
		return ((bool)rt_error(video->frame, "Invalid second in video frame"));
	if (!(video->frame[i].shape = read_shape(
		video_frame->value.array_v->inner[i].value.table_v)))
		video->frame[i].shape = NULL;
	else
		video->frame[i].shape->video = *video;
	if (!read_toml_type(video_frame->value.array_v->inner[i].value.table_v,
		&material, "material", TOML_Table))
		video->frame[i].material = NULL;
	else if (!(video->frame[i].material = read_material(
		material->value.table_v)))
		video->frame[i].material = NULL;
	if (video->frame[i].shape == NULL && video->frame[i].material == NULL)
	{
		return ((bool)rt_error(video->frame,
			"Invalid shape or material in video frame"));
	}
	return (true);
}

bool			read_video_frame(t_toml_table *toml,
	struct s_video_shape *video)
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
		if (read_video_second(video, video_frame, i) == false)
			return (false);
		i++;
	}
	return (true);
}

t_video			*read_video(t_toml_table *toml)
{
	t_video	*video;
	t_toml	*value;

	if (!(video = malloc(sizeof(*video))))
		return (rt_error(NULL, "Can not allocate video"));
	if (!(value = table_get(toml, "frame_sec")))
		return (rt_error(video, "Missing frame_sec in video"));
	if (read_digit(value, &video->frame_sec) == false)
		return (rt_error(video, "Invalid frame_sec in video"));
	if (!(value = table_get(toml, "secondes")))
		return (rt_error(video, "Missing secondes in video"));
	if (read_digit(value, &video->frame) == false)
		return (rt_error(video, "Invalid secondes in video"));
	video->frame *= video->frame_sec;
	return (video);
}
