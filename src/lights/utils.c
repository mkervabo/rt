#include "utils.h"
#include "config_utils.h"

bool		read_light_super(t_toml_table *toml, t_light *light)
{
	t_toml		*value;

	if (!(value = table_get(toml, "intensity")))
		light->intensity = 1;
	else if (!read_digit(value, &light->intensity))
		return (false);
	light->color = (t_color) { 255, 255, 255 };
	return true;
}
