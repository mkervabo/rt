#include "utils.h"
#include "config_utils.h"
#include "math/vec3.h"
#include <stdlib.h>
#include <math.h>

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
	object->video = (struct s_video_shape) { .video_len = 0, .frame_len = 0 };
	if (!read_video_shape(toml, &object->video))
		object->video.video_len = 0;
	if (!read_video_frame(toml, &object->video))
		object->video.frame_len = 0;
	return (true);
}

void			free_shape_super(t_shape *object)
{
	free(object->video.frame);
	free(object->video.video);
}
