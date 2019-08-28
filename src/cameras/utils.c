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
	if (!read_video_shape(toml, &camera->video))
		camera->video.video_len = 0;
	return (true);
}
