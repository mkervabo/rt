/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:33:22 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/12 14:50:20 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "toml.h"
# include "math/vec3.h"
# include "ray.h"
# include "color.h"
# include "video.h"

# include <stdint.h>

# define SHADOW_BIAS 1e-4

struct s_scene;

typedef struct	s_light
{
	uint8_t					type;
	t_color					color;
	double					intensity;
	double					decay;
	struct s_video_light	video;
}				t_light;

t_light			*read_light(t_toml_table *toml);
t_light			**read_lights(t_toml_table *toml, size_t *size);

bool			get_light_ray(const t_light *light, t_vec3 point,
				struct s_ray *ray);

double			receive_light(struct s_scene *scene, struct s_ray *light,
			t_vec3 p, t_color *color);
double			light_decay(t_vec3 origin, t_vec3 point, double decay);
void			free_light(t_light *light);

#endif
