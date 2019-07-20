/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:23:33 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/07/20 17:19:37 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_SPHERE_H
# define SHAPES_SPHERE_H

# include "shapes.h"

struct s_sphere {
	t_shape	super;
	double	r;
};

struct s_hit	hit_sphere(struct s_ray ray, struct s_sphere *sphere, struct s_intersection **intersections);
struct s_sphere	*read_sphere(t_toml_table *toml);

#endif
