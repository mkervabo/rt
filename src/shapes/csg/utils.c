/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:19:52 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/09 15:46:36 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "csg.h"
#include <stdlib.h>

size_t		min(size_t i, size_t j)
{
	if (i < j)
		return (i);
	return (j);
}

static void	swap(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void		sort4(double *a, double *b, double *c, double *d)
{
	if (*a > *b)
		swap(a, b);
	if (*c > *d)
		swap(c, d);
	if (*a > *c)
		swap(a, c);
	if (*b > *d)
		swap(b, d);
	if (*b > *c)
		swap(b, c);
}

void		init_v(size_t *len, struct s_intersection_tab *tab, size_t v[2],
	double d)
{
	*len = d;
	tab->len = 0;
	v[0] = 0;
	v[1] = 0;
}
