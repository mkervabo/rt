
#ifndef SPOT_POINT_LIGHT_H
# define SPOT_POINT_LIGHT_H

# include "light.h"

struct s_spot_light {
	t_light	super;
	t_vec3	position;
	t_vec3	direction;
	double	angle;
};

bool					spot_get_light_ray(const struct s_spot_light *light, t_vec3 point, struct s_ray *ray);
struct s_spot_light		*read_spot_light(t_toml_table *toml);
void					free_spot_light(struct s_spot_light *light);

#endif
