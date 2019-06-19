/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:16:32 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/28 14:35:33 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.h"

char				read_escape(t_reader *r)
{
	char c;

	c = reader_peek(r);
	if (c == 'n')
		return ('\n');
	else if (c == 't')
		return ('\t');
	else if (c == 'b')
		return ('\b');
	else if (c == 'f')
		return ('\f');
	else if (c == 'r')
		return ('\r');
	else
		return (c);
}

t_toml_error		read_quoted_key(t_reader *r, bool b, char **key)
{
	t_str	str;
	int16_t c;

	if (!(str = create_str(10)).inner)
		return (Error_Malloc);
	while ((c = reader_peek(r)) != -1 && c != (b ? '"' : '\''))
	{
		if (c == '\n')
			return (free_toml_string(str.inner) + Invalid_Key);
		if (c == '\\' && b)
		{
			reader_next(r);
			c = read_escape(r);
		}
		if (!append_char(&str, c))
			return (free_toml_string(str.inner) + Error_Malloc);
		reader_next(r);
	}
	if (c != -1)
		reader_next(r);
	if (!append_char(&str, '\0'))
		return (free_toml_string(str.inner) + Error_Malloc);
	*key = str.inner;
	return (No_Error);
}

static t_toml_error	read_bare_key(t_reader *r, char **key)
{
	t_str	str;
	int16_t c;

	if (!(str = create_str(10)).inner)
		return (Error_Malloc);
	while ((c = reader_peek(r)) != -1 && ((c >= 'A' && c <= 'Z')
				|| (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')
				|| c == '-' || c == '_'))
	{
		if (!append_char(&str, c))
			return (free_toml_string(str.inner) + Error_Malloc);
		reader_next(r);
	}
	if (!append_char(&str, '\0'))
		return (free_toml_string(str.inner) + Error_Malloc);
	*key = str.inner;
	return (No_Error);
}

t_toml_error		read_key(t_reader *r, char **str)
{
	if (reader_peek(r) == '"')
	{
		reader_next(r);
		return (read_quoted_key(r, true, str));
	}
	else if (reader_peek(r) == '\'')
	{
		reader_next(r);
		return (read_quoted_key(r, false, str));
	}
	else
		return (read_bare_key(r, str));
}
