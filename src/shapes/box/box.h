/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 19:59:34 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 16:17:55 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_BOX_H
# define SHAPES_BOX_H

# include "shape.h"

struct			s_box
{
	t_shape	super;
	t_vec3	bounds[2];
};

struct s_hit	hit_box(struct s_ray ray, struct s_box *box,
	struct s_intersection_tab *intersections);
struct s_hit	box_normal_and_uv(double min, struct s_ray *ray,
	struct s_box *box);
struct s_box	*read_box(t_toml_table *toml);
void			free_box(struct s_box *box);

#endif
