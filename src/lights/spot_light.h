/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot_light.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:28:43 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 14:47:25 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPOT_LIGHT_H
# define SPOT_LIGHT_H

# include "light.h"

struct					s_spot_light
{
	t_light	super;
	t_vec3	position;
	t_vec3	direction;
	double	angle;
};

bool					spot_get_light_ray(const struct s_spot_light *light,
	t_vec3 point, struct s_ray *ray);
struct s_spot_light		*read_spot_light(t_toml_table *toml);
void					free_spot_light(struct s_spot_light *light);

#endif
