#include "utils.h"
#include "config_utils.h"


static bool	read_color(t_toml_table *toml, t_color *color)
{
	t_toml	*value;

	if (!(value = table_get(toml, "r")))
		color->r = 0;
	else if (value->type != TOML_Integer)
		return ((bool)rt_error(NULL, "Is not a interger in red color"));
	else
		color->r = value->value.integer_v;
	if (!(value = table_get(toml, "g")))
		color->g = 0;
	else if (value->type != TOML_Integer)
		return ((bool)rt_error(NULL, "Is not a interger in green color"));
	else
		color->g = value->value.integer_v;
	if (!(value = table_get(toml, "b")))
		color->b = 0;
	else if (value->type != TOML_Integer)
		return ((bool)rt_error(NULL, "Is not a interger in blue color"));
	else
		color->b = value->value.integer_v;
	return (true);
}

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
