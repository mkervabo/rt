#include "toml.h"
#include "video.h"
#include "object.h"
#include "material.h"
#include <math.h>
#include "config_utils.h"
#include <stdlib.h>

bool					read_frame(struct s_frame *frame, t_toml_table *toml)
{
	t_toml			*f;
	t_toml			*value;

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

bool					read_video_shape(t_toml_table *toml, struct s_video_shape *video)
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
		if (!read_frame(video->video + i, frame->value.array_v->inner[i].value.table_v))
			return (false);//free tab 
		i++;
	}
	return  (true);
}

bool					read_video_frame(t_toml_table *toml, struct s_video_shape *video)
{
	t_toml			*video_frame;
	t_toml			*second;
	t_toml			*material;
	size_t			i;

	if (read_toml_type(toml, &video_frame, "video_frame", TOML_Array) == false)
		return (false);
	if (video_frame->value.array_v->len == 0
		|| video_frame->value.array_v->inner[0].type != TOML_Table)
		return (false);
	video->frame_len = video_frame->value.array_v->len;
	if (!(video->frame = malloc(sizeof(struct s_video_frame) * video->frame_len)))
		return (false);
	i = 0;
	while (i < video->frame_len)
	{
		if (!(second = table_get(video_frame->value.array_v->inner[i].value.table_v, "second")))
			return (false);
		else if (read_digit(second, &video->frame[i].second) == false)
			return (false);
		if (!(video->frame[i].shape = read_shape(video_frame->value.array_v->inner[i].value.table_v)))
			video->frame[i].shape = NULL;
		else {
			video->frame[i].shape->video = *video;
		}
		if (!read_toml_type(video_frame->value.array_v->inner[i].value.table_v, &material, "material", TOML_Table))
			video->frame[i].material = NULL;
		else if (!(video->frame[i].material = read_material(material->value.table_v)))
			video->frame[i].material = NULL;
		if (video->frame[i].shape == NULL && video->frame[i].material == NULL)
			return (false);//free tab
		i++;
	}
	return (true);
}

bool					read_video_light(t_toml_table *toml, struct s_video_light *video)
{
	t_toml			*video_frame;
	t_toml			*second;
	size_t			i;

	if (read_toml_type(toml, &video_frame, "video_frame", TOML_Array) == false)
		return (false);
	if (video_frame->value.array_v->len == 0
		|| video_frame->value.array_v->inner[0].type != TOML_Table)
		return (false);
	video->frame_len = video_frame->value.array_v->len;
	if (!(video->frame = malloc(sizeof(struct s_video_frame) * video->frame_len)))
		return (false);
	i = 0;
	while (i < video->frame_len)
	{
		if (!(second = table_get(video_frame->value.array_v->inner[i].value.table_v, "second")))
			return (false);
		else if (read_digit(second, &video->frame[i].second) == false)
			return (false);
		if (!(video->frame[i].light = read_light(video_frame->value.array_v->inner[i].value.table_v)))
			return (false);
		else
			video->frame[i].light->video = *video;
		i++;
	}
	return (true);
}