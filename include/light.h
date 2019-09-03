#ifndef LIGHT_H
#define LIGHT_H

#include "toml.h"
#include "math/vec3.h"
#include "color.h"

#include <stdint.h>

typedef struct	s_light {
	uint8_t	type;
}				t_light;

t_light			*read_light(t_toml_table *toml);

struct s_light_ray {
	t_vec3	direction;
	t_vec3	origin;
	t_color	color;
	double	intensity;
};

struct s_light_ray	get_light_ray(const t_light *light, t_vec3 point);

#endif
