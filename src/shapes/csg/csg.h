/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:02:16 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 16:08:00 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSG_H
# define CSG_H

# include "shape.h"

enum						e_csg_op
{
	CSG_UNION,
	CSG_DIFFERENCE,
	CSG_INTERSECTION
};

struct						s_csg
{
	t_shape			super;
	enum e_csg_op	op;
	t_shape			*first;
	t_shape			*second;
};

size_t						min(size_t i, size_t j);
void						sort4(double *a, double *b, double *c, double *d);
void						init_v(size_t *len,
	struct s_intersection_tab *tab, size_t v[2], double d);
struct s_intersection_tab	csg_union(struct s_intersection_tab first,
	struct s_intersection_tab second);
struct s_intersection_tab	csg_intersection(
	struct s_intersection_tab first, struct s_intersection_tab second);
struct s_intersection_tab	csg_difference(
	struct s_intersection_tab first, struct s_intersection_tab second);
struct s_hit				hit_csg(struct s_ray ray, struct s_csg *minus,
	struct s_intersection_tab *intersections);
struct s_csg				*read_csg(t_toml_table *toml, enum e_csg_op op);
void						free_csg(struct s_csg *csg);

#endif
