#include "point_light.h"
#include "light_types.h"
#include "utils.h"
#include "config_utils.h"
#include <stdlib.h>

bool			point_get_light_ray(const struct s_point_light *light, t_vec3 point, struct s_ray *ray) {
	*ray = (struct s_ray) {
		.direction = vec3_unit(vec3_sub(point, light->position)),
		.origin = light->position
	};
	return (true);
}

struct s_point_light	*read_point_light(t_toml_table *toml)
{
	struct s_point_light	*light;
	t_toml					*value;

	if (!(light = malloc(sizeof(*light))))
		return (rt_error(NULL, "Can not allocate point light"));
	if (!read_light_super(toml, &light->super))
		return (rt_error(light, "Invalid super in point light"));
	if (!read_toml_type(toml, &value, "position", TOML_Table))
		return (rt_error(light, "Missing position in point light"));
	if (!read_vec3(value->value.table_v, &light->position))
		return (rt_error(light, "Invalid position in point light"));
	light->super.type = LIGHT_POINT;
	return (light);
}

void					free_point_light(struct s_point_light *light)
{
	free_light_super(&light->super);
	free(light);
}