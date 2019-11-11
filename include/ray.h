/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:29:32 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/09/18 20:46:15 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "math/vec3.h"
# include <stdbool.h>
# include <stdint.h>

struct s_ray {
	struct s_vec3	origin;
	struct s_vec3	direction;
	float			n1;
	float			n2;
	uint8_t			depth;
};

t_vec3 ray_point_at(const struct s_ray *ray, float t);

#endif
