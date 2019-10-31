/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   difference.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:18:55 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/09 15:48:24 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "csg.h"
#include <stdlib.h>

static struct s_intersection_tab	tab_value(struct s_intersection f,
	struct s_intersection s, size_t v[2], struct s_intersection_tab tab)
{
	if (f.from < s.from)
		tab.inner[tab.len++] = (struct s_intersection) {
			.from = f.from,
			.to = s.from
		};
	if (f.to > s.to)
		tab.inner[tab.len++] = (struct s_intersection) {
			.from = s.to,
			.to = f.to
		};
	if (f.to < s.to)
		v[1]++;
	else
		v[0]++;
	return (tab);
}

struct s_intersection_tab			csg_difference(
	struct s_intersection_tab first, struct s_intersection_tab second)
{
	struct s_intersection		inter[2];
	struct s_intersection_tab	tab;
	size_t						v[2];
	size_t						len;

	if (second.len == 0)
		return (first);
	init_v(&len, &tab, v, first.len + second.len);
	tab.inner = malloc(len * sizeof(struct s_intersection));
	while (v[0] < first.len)
	{
		inter[0] = first.inner[v[0]];
		inter[1] = second.inner[min(v[1], second.len - 1)];
		if (inter[0].to < inter[1].to || v[1] >= second.len)
			v[0]++;
		else
			v[1]++;
		if (inter[0].to >= inter[1].from && inter[1].to >= inter[0].from)
			tab = tab_value(inter[0], inter[1], v, tab);
		else if (inter[0].to < inter[1].to || v[1] >= second.len)
			tab.inner[tab.len++] = inter[0];
	}
	while (v[0] < first.len)
		tab.inner[tab.len++] = first.inner[v[0]++];
	return (tab);
}
