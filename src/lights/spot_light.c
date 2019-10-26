#include "spot_light.h"
#include "light_types.h"
#include "utils.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>



bool			spot_get_light_ray(const struct s_spot_light *light, t_vec3 point, struct s_ray *ray)
{
	struct s_ray	lray;

	lray.direction = vec3_unit(vec3_sub(point, light->position));
	lray.origin = light->position;
	if (vec3_dot(lray.direction, light->direction) >= cos(light->angle * M_PI / 180))
	{
		*ray = (struct s_ray) {
			.direction = vec3_unit(vec3_sub(point, light->position)),
			.origin = light->position
		};
		return (true);
	}
	return (false);
}

struct s_spot_light		*read_spot_light(t_toml_table *toml)
{
	struct s_spot_light	*light;
	t_toml					*value;

	if (!(light = malloc(sizeof(*light))))
		return (rt_error(NULL, "Can not allocate spot light"));
	if (!read_light_super(toml, &light->super))
		return (rt_error(light, "Invalid super in spot light"));
	if (!read_toml_type(toml, &value, "position", TOML_Table))
		return (rt_error(light, "Missing position in spot light"));
	if (!read_vec3(value->value.table_v, &light->position))
		return (rt_error(light, "Invalid position in spot light"));
	if (!read_toml_type(toml, &value, "direction", TOML_Table))
		return (rt_error(light, "Missing direction in spot light"));
	if (!read_vec3(value->value.table_v, &light->direction))
		return (rt_error(light, "Invalid direction in spot light"));
	if (!(value = table_get(toml, "angle")))
		return (rt_error(light, "Missing angle in spot light"));
	if (!read_digit(value, &light->angle))
		return (rt_error(light, "Invalid angle in spot light"));
	light->direction = vec3_unit(light->direction);
	light->super.type = LIGHT_SPOT;
	return (light);
}
