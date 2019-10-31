/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:22:32 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/09 15:45:06 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "csg.h"
#include <stdlib.h>

static struct s_intersection_tab	tab_value_inter(
	struct s_intersection inter[2], struct s_intersection_tab tab)
{
	double	a;
	double	b;
	double	c;
	double	d;

	a = inter[0].from;
	b = inter[0].to;
	c = inter[1].from;
	d = inter[1].to;
	sort4(&a, &b, &c, &d);
	tab.inner[tab.len++] = (struct s_intersection) {
		.from = b,
		.to = c
	};
	return (tab);
}

struct s_intersection_tab			csg_intersection(
	struct s_intersection_tab first, struct s_intersection_tab second)
{
	struct s_intersection		inter[2];
	struct s_intersection_tab	tab;
	size_t						v[2];
	size_t						len;

	init_v(&len, &tab, v, first.len > second.len ? first.len : second.len);
	tab.inner = malloc((len + 1) * sizeof(struct s_intersection));
	while (v[0] < first.len && v[1] < second.len)
	{
		inter[0] = first.inner[v[0]];
		inter[1] = second.inner[v[1]];
		if (inter[0].to < inter[1].to)
			v[0]++;
		else
			v[1]++;
		if (inter[0].to >= inter[1].from && inter[1].to >= inter[0].from)
			tab = tab_value_inter(inter, tab);
	}
	return (tab);
}
