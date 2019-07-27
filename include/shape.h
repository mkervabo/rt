/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:07:46 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/07/20 17:15:07 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "ray.h"
# include "color.h"
//# include "math/vec2.h"
# include "math/vec3.h"
# include "toml.h"
# include "object.h"
# include <stdint.h>

struct s_intersection {
	double	from;
	double	to;
};

typedef struct	s_shape {
	uint8_t			type;
	struct s_vec3	position;
	struct s_vec3	rotation;
}				t_shape;

struct s_hit {
	//struct s_vec2			uv;
	struct s_vec3			normal;
	double					t;
	struct s_object			*who;
};

struct s_hit	hit_shape(struct s_ray ray, t_shape *shape, struct s_intersection **intersections);
t_shape			*read_shape(t_toml_table *toml);

#endif
