/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:16:14 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/22 13:46:52 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.h"

static float	read_integer(t_reader *r, bool *s)
{
	float	num;
	int16_t	c;

	*s = false;
	num = 0;
	c = reader_peek(r);
	if (c == '-')
		*s = true;
	if (c == '-' || c == '+')
		reader_next(r);
	while ((c = reader_peek(r)) != -1 && ((c >= '0' && c <= '9') || c == '_'))
	{
		if (c >= '0' && c <= '9')
			num = num * 10 + (c - 48);
		reader_next(r);
	}
	return (num);
}

static double	read_float(t_reader *r)
{
	double	num;
	size_t	i;
	int16_t c;

	i = 0;
	num = 0;
	while ((c = reader_peek(r)) != -1 && ((c >= '0' && c <= '9') || c == '_'))
	{
		if (c >= '0' && c <= '9')
		{
			num = num * 10 + (c - 48);
			i++;
		}
		reader_next(r);
	}
	while (i-- > 0)
		num *= 0.1;
	return (num);
}

t_toml			read_toml_digit(t_reader *r)
{
	float	integer;
	bool	sign;

	integer = read_integer(r, &sign);
	if (reader_peek(r) == '.')
	{
		reader_next(r);
		return ((t_toml) {
			TOML_Float,
			{
				.float_v = (sign ? -1 : 1) * ((double)integer + read_float(r))
			}
		});
	}
	return ((t_toml) {
		TOML_Integer,
		{
			.integer_v = sign ? -integer : integer
		}
	});
}
