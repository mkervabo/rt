/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:21:46 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/14 08:51:09 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "config_utils.h"
#include "math/vec3.h"
#include <stdlib.h>
#include <math.h>

static void	read_shape_super_video(t_toml_table *toml, t_shape *object)
{
	if (!read_video_shape(toml, &object->video))
	{
		object->video.video_len = 0;
		object->video.video = NULL;
	}
	if (!read_video_frame(toml, &object->video))
	{
		object->video.frame_len = 0;
		object->video.frame = NULL;
	}
}

bool		read_shape_super(t_toml_table *toml, t_shape *object)
{
	t_toml		*value;

	if (read_toml_type(toml, &value, "position", TOML_Table))
	{
		if (!read_vec3(value->value.table_v, &object->position))
			return ((bool)rt_error(NULL, "Invalid shape position"));
	}
	else
		object->position = vec3(0, 0, 0);
	if (read_toml_type(toml, &value, "rotation", TOML_Table))
	{
		if (!read_vec3(value->value.table_v, &object->rotation))
			return ((bool)rt_error(NULL, "Invalid shape rotation"));
		object->rotation = vec3_multv(object->rotation, M_PI / 180);
	}
	else
		object->rotation = vec3(0, 0, 0);
	read_shape_super_video(toml, object);
	return (true);
}

void		free_shape_super(t_shape *object)
{
	free(object->video.frame);
	free(object->video.video);
}
