/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:20:12 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/09 15:53:05 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "shape.h"

struct				s_cylinder
{
	t_shape super;
	double	r;
};

struct s_hit		hit_cylinder(struct s_ray ray, struct s_cylinder *cylinder,
					struct s_intersection_tab *intersections);
struct s_cylinder	*read_cylinder(t_toml_table *toml);
void				free_cylinder(struct s_cylinder *cylinder);

#endif
