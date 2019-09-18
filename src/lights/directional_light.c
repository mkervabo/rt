#include "directional_light.h"
#include "light_types.h"
#include "utils.h"
#include "config_utils.h"
#include <stdlib.h>

struct s_ray			directional_get_light_ray(const struct s_directional_light *light, t_vec3 point) {
	double	denom;
	double	t;

	denom = vec3_dot(light->direction, vec3_multv(light->direction, -1));
	t = vec3_dot(vec3_sub(light->position, point), light->direction) / denom;

	return ((struct s_ray) {
		.direction = light->direction,
		.origin = vec3_add(point, vec3_multv(light->direction, -t))
	});
}

struct s_directional_light	*read_directional_light(t_toml_table *toml)
{
	struct s_directional_light	*light;
	t_toml						*value;

	if (!(light = malloc(sizeof(*light))))
		return (rt_error(NULL, "Can not allocate directional light"));
	if (!read_light_super(toml, &light->super))
		return (rt_error(light, "Invalid super in directional light"));
	if (!read_toml_type(toml, &value, "position", TOML_Table))
		return (rt_error(light, "Missing position in directional light"));
	if (!read_vec3(value->value.table_v, &light->position))
		return (rt_error(light, "Invalid position in directional light"));
	if (!read_toml_type(toml, &value, "direction", TOML_Table))
		return (rt_error(light, "Misssing direction in directional light"));
	if (!read_vec3(value->value.table_v, &light->direction))
		return(rt_error(light, "Invalid direction in directional light"));
	if (vec3_is_zero(light->direction))
		return (rt_error(light, "Invalid direction in directional light"));
	light->direction = vec3_unit(light->direction);
	light->super.type = LIGHT_DIRECTIONAL;
	return (light);
}
