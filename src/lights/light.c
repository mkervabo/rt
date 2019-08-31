#include "light.h"
#include "debug/assert.h"
#include "toml.h"

#include "light_types.h"
#include "point_light.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

struct s_light_ray	get_light_ray(const t_light *light, t_vec3 point) {
	if (light->type == LIGHT_POINT)
		return point_get_light_ray((const struct s_point_light *)light, point);
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
	else
		return (NULL);
}
