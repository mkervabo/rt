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
		return (NULL);
	if (!read_light_super(toml, &light->super))
		return (nfree(light));
	if (!read_toml_type(toml, &value, "position", TOML_Table))
		return (nfree(light));
	if (!read_vec3(value->value.table_v, &light->position))
		return (nfree(light));
	if (!read_toml_type(toml, &value, "direction", TOML_Table))
		return (nfree(light));
	if (!read_vec3(value->value.table_v, &light->direction))
		return (nfree(light));
	if (vec3_is_zero(light->direction))
		return (nfree(light));
	light->direction = vec3_unit(light->direction);
	light->super.type = LIGHT_DIRECTIONAL;
	return (light);
}
