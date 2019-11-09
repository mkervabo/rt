/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:21:45 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/11/09 15:25:35 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_TYPE_H
# define SHAPE_TYPE_H

#include "shape.h"

enum e_shape_type {
	SHAPE_SPHERE,
	SHAPE_CYLINDER,
	SHAPE_CONE,
	SHAPE_PLANE,
	SHAPE_BOX,
	SHAPE_TRIANGLE,
	SHAPE_DISK,
	SHAPE_PARABOLOID,
	SHAPE_CSG,
	SHAPE_GROUP,
	SHAPE_OBJ
};

struct	s_shape_record {
	const char	*name;
	struct s_hit	(*hit)(struct s_ray, t_shape *, struct s_intersection_tab *);
	t_shape		*(*read)(t_toml_table *toml);
};

#endif
