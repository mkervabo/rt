/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:05:36 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/05 16:05:37 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "shape.h"

struct			s_cone
{
	t_shape	super;
	double	angle;
	bool	revolution;
};

struct s_hit	hit_cone(struct s_ray ray, struct s_cone *sphere,
				struct s_intersection_tab *intersections);
struct s_cone	*read_cone(t_toml_table *toml);
void			free_cone(struct s_cone *cone);

#endif
