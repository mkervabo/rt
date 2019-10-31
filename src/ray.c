/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:05:13 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/02 16:05:15 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

struct s_vec3	ray_point_at(const struct s_ray *ray, float t)
{
	return (vec3_add(ray->origin, vec3_multv(ray->direction, t)));
}
