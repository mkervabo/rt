/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:24:33 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/09 15:49:20 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "csg.h"
#include <stdlib.h>

static void							give_v(struct s_intersection inter[2],
	size_t v[2], struct s_intersection_tab first,
	struct s_intersection_tab second)
{
	inter[0] = first.inner[v[0]];
	inter[1] = second.inner[v[1]];
	if (inter[0].to < inter[1].to)
		v[0]++;
	else
		v[1]++;
}

static void							give_tab_v(struct s_intersection inter[2],
									struct s_intersection_tab *tab)
{
	if (inter[0].to < inter[1].to)
		tab->inner[tab->len++] = inter[0];
	else
		tab->inner[tab->len++] = inter[1];
}

static struct s_intersection_tab	tab_value_union(
	struct s_intersection inter[2], struct s_intersection_tab tab, size_t v[2])
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
		.from = a,
		.to = d
	};
	if (inter[0].to < inter[1].to)
		v[1]++;
	else
		v[0]++;
	return (tab);
}

struct s_intersection_tab			csg_union(struct s_intersection_tab first,
	struct s_intersection_tab second)
{
	struct s_intersection		inter[2];
	struct s_intersection_tab	tab;
	size_t						v[2];
	size_t						len;

	init_v(&len, &tab, v, first.len + second.len);
	tab.inner = malloc((len + 1) * sizeof(struct s_intersection));
	while (v[0] < first.len && v[1] < second.len)
	{
		give_v(inter, v, first, second);
		if ((inter[0].from < inter[1].from && inter[0].to > inter[1].to)
		|| (inter[1].from < inter[0].from && inter[1].to > inter[0].to))
			continue;
		if (inter[0].to >= inter[1].from && inter[1].to >= inter[0].from)
			tab = tab_value_union(inter, tab, v);
		else
			give_tab_v(inter, &tab);
	}
	while (v[0] < first.len)
		tab.inner[tab.len++] = first.inner[v[0]++];
	while (v[1] < second.len)
		tab.inner[tab.len++] = second.inner[v[1]++];
	return (tab);
}
