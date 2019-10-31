/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:17:05 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/05 13:18:32 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/utils.h"

void	scale(double *a, double *b, double max)
{
	double	total;

	total = *a + *b;
	if (total)
	{
		*a *= max / total;
		*b *= max / total;
	}
}

double	clamp(double value, double from, double to)
{
	if (value > to)
		return (to);
	else if (value < from)
		return (from);
	else
		return (value);
}

void	dswap(double *a, double *b)
{
	double	c;

	c = *a;
	*a = *b;
	*b = c;
}
