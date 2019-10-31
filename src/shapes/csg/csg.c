/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:51:56 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/12 13:55:12 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "csg.h"
#include "../shape_types.h"
#include "../utils.h"
#include "math/quadratic.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>
#include "toml.h"

static void		give_value(struct s_intersection_tab t[3], struct s_hit hit[2],
	struct s_ray ray, struct s_csg *csg)
{
	t[0] = (struct s_intersection_tab) { .len = 0 };
	t[1] = (struct s_intersection_tab) { .len = 0 };
	hit[0] = hit_shape(ray, csg->first, &t[0]);
	hit[1] = hit_shape(ray, csg->second, &t[1]);
}

struct s_hit	hit_csg(struct s_ray ray, struct s_csg *csg,
	struct s_intersection_tab *intersections)
{
	struct s_hit				hit[2];
	struct s_intersection_tab	t[3];
	bool						is_first;

	give_value(t, hit, ray, csg);
	if (csg->op == CSG_DIFFERENCE)
		t[2] = csg_difference(t[0], t[1]);
	else if (csg->op == CSG_INTERSECTION)
		t[2] = csg_intersection(t[0], t[1]);
	else
		t[2] = csg_union(t[0], t[1]);
	if (t[2].len != 0)
		is_first = t[0].len > 0 && (t[2].inner[0].from == t[0].inner[0].to
			|| t[2].inner[0].from == t[0].inner[0].from);
	if (t[0].inner != t[2].inner)
		free(t[0].inner);
	free(t[1].inner);
	if (intersections)
		*intersections = t[2];
	else
		free(t[2].inner);
	if (t[2].len == 0)
		return ((struct s_hit) { .t = -1 });
	return (is_first ? hit[0] : hit[1]);
}

struct s_csg	*read_csg(t_toml_table *toml,
	enum e_csg_op op)
{
	struct s_csg	*csg;
	t_toml			*value;

	if (!(csg = malloc(sizeof(struct s_csg))))
		return (rt_error(NULL, "Can not allocate csg shape"));
	if (!read_shape_super(toml, &csg->super))
		return (rt_error(csg, "Invalid super in csg shape"));
	if (!(value = table_get(toml, "first")))
		return (rt_error(csg, "Missing first in csg shape"));
	if ((csg->first = read_shape(value->value.table_v)) == NULL)
		return (rt_error(csg, "Invalid first in csg shape"));
	if (!(value = table_get(toml, "second")))
	{
		free_shape(csg->first);
		return (rt_error(csg, "Misssing second in csg shape"));
	}
	if ((csg->second = read_shape(value->value.table_v)) == NULL)
	{
		free_shape(csg->first);
		return (rt_error(csg, "Invalid second in csg shape"));
	}
	csg->super.type = SHAPE_CSG;
	csg->op = op;
	return (csg);
}

void			free_csg(struct s_csg *csg)
{
	free_shape_super(&csg->super);
	free_shape(csg->first);
	free_shape(csg->second);
	free(csg);
}
