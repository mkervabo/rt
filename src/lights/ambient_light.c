#include "ambient_light.h"
#include "light_types.h"
#include "config_utils.h"
#include <stdlib.h>

struct s_light_ray		ambient_get_light_ray(const struct s_ambient_light *light, t_vec3 point) {
	return ((struct s_light_ray) {
		.intensity = light->intensity
	});
}

struct s_ambient_light	*read_ambient_light(t_toml_table *toml)
{
	struct s_ambient_light	*light;
	t_toml					*value;

	if (!(light = malloc(sizeof(*light))))
		return (NULL);
	if (!(value = table_get(toml, "intensity")))
		light->intensity = 1;
	else if (!read_digit(value, &light->intensity))
		return (nfree(light));
	light->super.type = LIGHT_AMBIENT;
	return (light);
}
