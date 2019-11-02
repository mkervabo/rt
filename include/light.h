#ifndef LIGHT_H
#define LIGHT_H

#include "toml.h"
#include "math/vec3.h"
#include "ray.h"
#include "color.h"
#include "video.h"

#include <stdint.h>

# define SHADOW_BIAS 1e-4

struct s_scene;

typedef struct	s_light {
	uint8_t				type;
	t_color				color;
	double				intensity;
	double				decay;
	struct s_video_light video;
}				t_light;

t_light			*read_light(t_toml_table *toml);

bool	get_light_ray(const t_light *light, t_vec3 point, struct s_ray *ray);

bool	receive_light(struct s_scene *scene, struct s_ray *light, t_vec3 p, double *value);
double	light_decay(t_vec3 origin, t_vec3 point, double decay);

#endif
