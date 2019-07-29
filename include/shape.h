/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:07:46 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/07/30 18:26:38 by mkervabo         ###   ########.fr       */
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

struct s_intersection_tab {
	size_t					len;
	struct s_intersection	*inner;
};

typedef struct	s_shape {
	uint8_t			type;
	struct s_vec3	position;
	struct s_vec3	rotation;
}				t_shape;

struct s_hit {
	struct s_vec3			normal;
	double					t;
	float					u;
	float					v;
	struct s_object			*who;
};

struct s_hit	hit_shape(struct s_ray ray, t_shape *shape, struct s_intersection_tab *intersections);
t_shape			*read_shape(t_toml_table *toml);

#endif
