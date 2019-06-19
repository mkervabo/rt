/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:22:06 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/22 13:46:33 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.h"

static bool		reader_expect(t_reader *r, const char *expected)
{
	while (*expected)
		if (reader_peek(r) == *expected)
		{
			reader_next(r);
			expected++;
		}
		else
			return (false);
	return (true);
}

t_toml_error	read_boolean(t_reader *r, t_toml *tom)
{
	tom->type = TOML_Boolean;
	if (reader_peek(r) == 't')
	{
		if (reader_expect(r, "true"))
			tom->value.boolean_v = true;
		else
			return (Invalid_Bool);
	}
	else
	{
		if (reader_expect(r, "false"))
			tom->value.boolean_v = false;
		else
			return (Invalid_Bool);
	}
	return (No_Error);
}
