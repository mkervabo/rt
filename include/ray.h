/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:29:32 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/11/05 14:37:58 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "math/vec3.h"
# include <stdbool.h>
# include <stddef.h>

struct	s_ray
{
	struct s_vec3	origin;
	struct s_vec3	direction;
	double			n1;
	double			n2;
	size_t			depth;
};

t_vec3	ray_point_at(const struct s_ray *ray, float t);

#endif
