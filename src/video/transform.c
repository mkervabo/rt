/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:02:26 by mkervabo          #+#    #+#             */
/*   Updated: 2019/10/31 13:04:31 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video.h"
#include "config.h"

static void		new_camera_position(struct s_camera *camera, size_t frame,
	double frame_sec)
{
	size_t i;
	double from;
	double to;

	i = 0;
	while (i < camera->video.video_len)
	{
		from = camera->video.video[i].from * frame_sec;
		to = camera->video.video[i].to * frame_sec;
		if (frame > from && frame <= to)
		{
			camera->position = vec3_add(camera->position,
				vec3_divv(camera->video.video[i].position, to - from));
			camera->rotation = vec3_add(camera->rotation,
				vec3_divv(camera->video.video[i].rotation, to - from));
		}
		i++;
	}
}

static void		new_object_position(t_object *object, size_t frame,
	double frame_sec)
{
	size_t i;
	double from;
	double to;

	i = 0;
	while (i < object->shape->video.video_len)
	{
		from = object->shape->video.video[i].from * frame_sec;
		to = object->shape->video.video[i].to * frame_sec;
		if (frame > from && frame <= to)
		{
			object->shape->position = vec3_add(object->shape->position,
				vec3_divv(object->shape->video.video[i].position, to - from));
			object->shape->rotation = vec3_add(object->shape->rotation,
				vec3_divv(object->shape->video.video[i].rotation, to - from));
		}
		i++;
	}
}

static void		new_object_material(t_object *object, size_t frame,
	double frame_sec)
{
	size_t	i;
	size_t	second;
	t_vec3	position;
	t_vec3	rotation;

	i = 0;
	while (i < object->shape->video.frame_len)
	{
		second = object->shape->video.frame[i].second * frame_sec;
		if (frame == second)
		{
			position = object->shape->position;
			rotation = object->shape->rotation;
			if (object->shape->video.frame[i].shape != NULL)
				object->shape = object->shape->video.frame[i].shape;
			if (object->shape->video.frame[i].material != NULL)
				object->material = object->shape->video.frame[i].material;
			object->shape->position = position;
			object->shape->rotation = rotation;
		}
		i++;
	}
}

static void		new_light_type(t_light **light, size_t frame,
	double frame_sec)
{
	size_t	i;
	size_t	second;

	i = 0;
	while (i < (*light)->video.frame_len)
	{
		second = (*light)->video.frame[i].second * frame_sec;
		if (frame == second)
		{
			if ((*light)->video.frame[i].light != NULL)
				*light = (*light)->video.frame[i].light;
		}
		i++;
	}
}

void			video_transform_scene(struct s_config *config, size_t frame)
{
	size_t i;

	if (config->video == NULL)
		return ;
	i = 0;
	while (i < config->scene.objects_size)
	{
		new_object_position(&config->scene.objects[i],
			frame, config->video->frame_sec);
		new_object_material(&config->scene.objects[i],
			frame, config->video->frame_sec);
		i++;
	}
	i = 0;
	while (i < config->scene.lights_size)
	{
		new_light_type(&config->scene.lights[i],
			frame, config->video->frame_sec);
		i++;
	}
	new_camera_position(config->scene.camera, frame, config->video->frame_sec);
}
