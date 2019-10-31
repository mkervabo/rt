/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_light.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:27:21 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:30:58 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_POINT_LIGHT_H
# define LIGHTS_POINT_LIGHT_H

# include "light.h"

struct					s_point_light
{
	t_light	super;
	t_vec3	position;
};

bool					point_get_light_ray(const struct s_point_light *light,
	t_vec3 point, struct s_ray *ray);
struct s_point_light	*read_point_light(t_toml_table *toml);
void					free_point_light(struct s_point_light *light);

#endif
