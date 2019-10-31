/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_shape.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:49:32 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/05 16:49:33 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_OBJ_SHAPE_H
# define SHAPES_OBJ_SHAPE_H

# include "shape.h"
# include "triangle.h"

struct				s_obj_shape
{
	t_shape				super;
	struct s_triangle	*triangles;
	size_t				size;
};

struct s_hit		hit_obj_shape(struct s_ray ray, struct s_obj_shape *obj,
	struct s_intersection_tab *intersections);
struct s_obj_shape	*read_obj_shape(t_toml_table *toml);
void				free_obj_shape(struct s_obj_shape *obj);

#endif
