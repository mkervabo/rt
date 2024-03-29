#ifndef LIGHTS_AMBIENT_LIGHT_H
# define LIGHTS_AMBIENT_LIGHT_H

# include "light.h"

struct s_ambient_light {
	t_light	super;
};

bool					ambient_get_light_ray(const struct s_ambient_light *light, t_vec3 point, struct s_ray *ray);
struct s_ambient_light	*read_ambient_light(t_toml_table *toml);
void					free_ambient_light(struct s_ambient_light *light);
#endif
