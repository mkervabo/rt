/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:01:10 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/06 11:01:11 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISK_H
# define DISK_H

# include "shape.h"

struct			s_disk
{
	t_shape	super;
	double	radius;
	double	inner_radius;
	double	angle;
};

struct s_hit	hit_disk(struct s_ray ray, struct s_disk *disk,
				struct s_intersection_tab *intersections);
struct s_disk	*read_disk(t_toml_table *toml);
void			free_disk(struct s_disk	*disk);

#endif
