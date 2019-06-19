/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 21:39:06 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/22 13:52:37 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.h"

static t_toml_error	read_literal_string(t_reader *r, char **str)
{
	reader_next(r);
	if (reader_peek(r) == '\'')
	{
		reader_next(r);
		if (reader_peek(r) == '\'')
			return (read_multi_string(r, false, str));
		*str = "\0";
		return (No_Error);
	}
	return (read_quoted_key(r, false, str));
}

static t_toml_error	read_basic_string(t_reader *r, char **str)
{
	reader_next(r);
	if (reader_peek(r) == '"')
	{
		reader_next(r);
		if (reader_peek(r) == '"')
			return (read_multi_string(r, true, str));
		*str = "\0";
		return (No_Error);
	}
	return (read_quoted_key(r, true, str));
}

t_toml_error		read_string(t_reader *r, t_toml *tom)
{
	int				c;
	char			*str;
	t_toml_error	err;

	c = reader_peek(r);
	if (c == '"')
		err = read_basic_string(r, &str);
	else if (c == '\'')
		err = read_literal_string(r, &str);
	else
		return (Invalid_String);
	*tom = (t_toml) {
			TOML_String,
			{
				.string_v = str
			}
	};
	return (err);
}
