/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:29:32 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/08/15 13:20:02 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "math/vec3.h"

struct s_ray {
	struct s_vec3	origin;
	struct s_vec3	direction;
};

t_vec3 ray_point_at(struct s_ray *ray, float t);

#endif
