/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:23:33 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/11/07 10:35:16 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_SPHERE_H
# define SHAPES_SPHERE_H

# include "shape.h"

struct s_sphere {
	t_shape	super;
	double	r;
};

struct s_hit	hit_sphere(struct s_ray ray, struct s_sphere *sphere, struct s_intersection_tab *intersections);
struct s_sphere	*read_sphere(t_toml_table *toml);
void			free_sphere(struct s_sphere *sphere);

#endif
