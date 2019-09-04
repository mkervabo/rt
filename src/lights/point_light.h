#ifndef LIGHTS_POINT_LIGHT_H
# define LIGHTS_POINT_LIGHT_H

# include "light.h"

struct s_point_light {
	t_light	super;
	t_vec3	position;
};

struct s_ray			point_get_light_ray(const struct s_point_light *light, t_vec3 point);
struct s_point_light	*read_point_light(t_toml_table *toml);

#endif
