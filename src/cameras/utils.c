/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:19:08 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/02 17:19:09 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "config_utils.h"
#include "math/vec3.h"
#include <stdlib.h>
#include <math.h>

bool	read_camera_super(t_toml_table *toml, struct s_camera *camera)
{
	t_toml		*value;

	if (read_toml_type(toml, &value, "position", TOML_Table))
	{
		if (!read_vec3(value->value.table_v, &camera->position))
			return ((bool)rt_error(NULL, "Invalid camera position"));
	}
	else
		camera->position = vec3(0, 0, 0);
	if (read_toml_type(toml, &value, "rotation", TOML_Table))
	{
		if (!read_vec3(value->value.table_v, &camera->rotation))
			return ((bool)rt_error(NULL, "Invalid camera rotation"));
		camera->rotation = vec3_multv(camera->rotation, M_PI / 180);
	}
	else
		camera->rotation = vec3(0, 0, 0);
	camera->video = (struct s_video_shape) { .video_len = 0, .frame_len = 0 };
	read_video_shape(toml, &camera->video);
	return (true);
}

void	free_camera_super(struct s_camera *camera)
{
	free(camera->video.video);
	free(camera->video.frame);
}
