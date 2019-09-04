#ifndef LIGHTS_AMBIENT_LIGHT_H
# define LIGHTS_AMBIENT_LIGHT_H

# include "light.h"

struct s_ambient_light {
	t_light	super;
};

struct s_ray			ambient_get_light_ray(const struct s_ambient_light *light, t_vec3 point);
struct s_ambient_light	*read_ambient_light(t_toml_table *toml);

#endif
