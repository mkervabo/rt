#include "light.h"
#include "debug/assert.h"
#include "toml.h"
#include "config_utils.h"

#include "light_types.h"
#include "point_light.h"
#include "ambient_light.h"
#include "directional_light.h"
#include "spot_light.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

bool	get_light_ray(const t_light *light, t_vec3 point, struct s_ray *ray)
{
	if (light->type == LIGHT_POINT)
		return (point_get_light_ray((const struct s_point_light *)light, point, ray));
	else if (light->type == LIGHT_AMBIENT)
		return (ambient_get_light_ray((const struct s_ambient_light *)light, point, ray));
	else if (light->type == LIGHT_DIRECTIONAL)
		return (directional_get_light_ray((const struct s_directional_light *)light, point, ray));
	else if (light->type == LIGHT_SPOT)
		return (spot_get_light_ray((const struct s_spot_light *)light, point, ray));
	else
		assertf(false, "Unimplemented light type: %d", light->type);
}

t_light			*read_light(t_toml_table *toml)
{
	t_toml	*type;

	if (!(type = table_get(toml, "type")))
		return (NULL);
	if (type->type != TOML_String)
		return (NULL);
	if (ft_strcmp(type->value.string_v, "POINT") == 0)
		return ((t_light *)read_point_light(toml));
	else if (ft_strcmp(type->value.string_v, "AMBIENT") == 0)
		return ((t_light *)read_ambient_light(toml));
	else if (ft_strcmp(type->value.string_v, "DIRECTIONAL") == 0)
		return ((t_light *)read_directional_light(toml));
	else if (ft_strcmp(type->value.string_v, "SPOT") == 0)
		return ((t_light *)read_spot_light(toml));
	else
		return (rt_error(NULL, "Invalid light type"));
}
