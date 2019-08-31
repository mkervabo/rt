#include "point_light.h"
#include "light_types.h"
#include "config_utils.h"
#include <stdlib.h>

struct s_light_ray		point_get_light_ray(const struct s_point_light *light, t_vec3 point) {
	return ((struct s_light_ray) {
		.direction = vec3_unit(vec3_sub(point, light->position)),
		.origin = light->position,
		.intensity = light->intensity
	});
}

struct s_point_light	*read_point_light(t_toml_table *toml)
{
	struct s_point_light	*light;
	t_toml					*value;

	if (!(light = malloc(sizeof(*light))))
		return (NULL);
	if (!read_toml_type(toml, &value, "position", TOML_Table))
		return (nfree(light));
	if (!read_vec3(value->value.table_v, &light->position))
		return (nfree(light));
	if (!(value = table_get(toml, "intensity")))
		light->intensity = 1;
	else if (!read_digit(value, &light->intensity))
		return (nfree(light));
	light->super.type = LIGHT_POINT;
	return (light);
}
