#include "utils.h"
#include "config_utils.h"

bool		read_light_super(t_toml_table *toml, t_light *light)
{
	t_toml		*value;

	if (!(value = table_get(toml, "intensity")))
		light->intensity = 1;
	else if (!read_digit(value, &light->intensity))
		return ((bool)rt_error(NULL, "intensity is not a number"));
	if (!(value = table_get(toml, "decay")))
		light->decay = 0;
	else if (!read_digit(value, &light->decay))
		return ((bool)rt_error(NULL, "decay is not a number"));
	if (!(value = table_get(toml, "color")))
		light->color = (t_color) { 255, 255, 255 };
	else if (!read_color(value->value.table_v, &light->color))
		return ((bool)rt_error(NULL, "Invalid color in read light super"));
	if (!read_video_light(toml, &light->video))
		light->video.frame_len = 0;
	return (true);
}
