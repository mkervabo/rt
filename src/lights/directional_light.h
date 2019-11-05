#ifndef LIGHTS_DIRECTIONAL_LIGHT_H
# define LIGHTS_DIRECTIONAL_LIGHT_H

# include "light.h"

struct s_directional_light {
	t_light	super;
	t_vec3	position;
	t_vec3	direction;
};

bool						directional_get_light_ray(const struct s_directional_light *light, t_vec3 point, struct s_ray *ray);
struct s_directional_light	*read_directional_light(t_toml_table *toml);
void						free_directional_light(struct s_directional_light *light);

#endif
