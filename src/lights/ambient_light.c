#include "ambient_light.h"
#include "light_types.h"
#include "utils.h"
#include "config_utils.h"
#include <stdlib.h>

struct s_ray		ambient_get_light_ray(const struct s_ambient_light *light, t_vec3 point) {
	return ((struct s_ray) {});
}

struct s_ambient_light	*read_ambient_light(t_toml_table *toml)
{
	struct s_ambient_light	*light;
	t_toml					*value;

	if (!(light = malloc(sizeof(*light))))
		return (rt_error(NULL, "Can not allocate ambient light"));
	if (!read_light_super(toml, &light->super))
		return (rt_error(light, "Invalid ambient light"));
	light->super.type = LIGHT_AMBIENT;
	return (light);
}
