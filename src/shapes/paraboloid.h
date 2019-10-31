/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:28:58 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 15:01:38 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARABOLOID_H
# define PARABOLOID_H

# include "shape.h"

struct				s_paraboloid
{
	t_shape	super;
	double	r;
	double	h;
};

struct s_hit		hit_paraboloid(struct s_ray ray,
					struct s_paraboloid *paraboloid,
					struct s_intersection_tab *intersections);
struct s_paraboloid	*read_paraboloid(t_toml_table *toml);
void				free_paraboloid(struct s_paraboloid *paraboloid);

#endif
