/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:56:17 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/28 14:36:49 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.h"
#include <stdlib.h>

t_toml				create_toml_table(t_toml_table *value)
{
	return ((t_toml) {
		TOML_Table,
		{
			.table_v = value
		}
	});
}

static t_toml_error	which_array_table(t_toml_table *petit_poisson,
	t_toml_array **tom_array, char *key)
{
	t_toml			*value;

	if ((value = table_get(petit_poisson, key)))
	{
		if (value->type != TOML_Array)
			return (Invalid_Array);
		*tom_array = value->value.array_v;
		free(key);
	}
	else
	{
		if (!(*tom_array = create_array(10)))
			return (Error_Malloc);
		if (!append_table(petit_poisson, key, (t_toml) {
					TOML_Array,
					{
						.array_v = *tom_array
					}
				}))
			return (free_toml_array(*tom_array) + Error_Malloc);
	}
	return (No_Error);
}

static t_toml_error	read_array_table(t_reader *r, t_toml_table *petit_poisson,
	char *key)
{
	t_toml_array	*tom_array;
	t_toml_table	*table;
	t_toml_error	err;

	if (reader_peek(r) != ']')
		return (Invalid_Table_Header);
	reader_next(r);
	if ((err = which_array_table(petit_poisson, &tom_array, key)) != No_Error)
		return (err);
	if ((err = read_toml(r, &table, false)) != No_Error)
		return (err);
	if (!append_array(tom_array, create_toml_table(table)))
		return (Error_Malloc);
	return (No_Error);
}

t_toml_error		read_table(t_reader *r, t_toml_table *gros_poisson)
{
	bool			array;
	t_toml_table	*petit_poisson;
	char			*key;
	t_toml_error	err;
	t_toml_table	*value;

	err = No_Error;
	reader_next(r);
	if ((array = (reader_peek(r) == '[')))
		reader_next(r);
	petit_poisson = gros_poisson;
	if ((err = read_dotted_key(r, &petit_poisson, &key)) != No_Error)
		return (err);
	if (reader_peek(r) != ']')
		return (Invalid_Table_Header);
	reader_next(r);
	if (array)
		err = read_array_table(r, petit_poisson, key);
	else
	{
		if ((err = read_toml(r, &value, false)) == No_Error)
			if (!append_table(petit_poisson, key, create_toml_table(value)))
				err = Error_Malloc;
	}
	return (err);
}

t_toml_error		read_inline_table(t_reader *r, t_toml *tom)
{
	t_toml_table	*gros_poisson;
	t_toml_error	err;
	int16_t			c;

	if (!(gros_poisson = create_table(10)))
		return (Error_Malloc);
	reader_next(r);
	skip_ws(r, false);
	while ((c = reader_peek(r)) != -1 && c != '}')
	{
		if ((err = read_key_val(r, gros_poisson)) != No_Error)
			return (free_toml_table(gros_poisson) + err);
		skip_ws(r, false);
		if (reader_peek(r) == ',')
			reader_next(r);
		else if (reader_peek(r) != '}')
			return (free_toml_table(gros_poisson) + Invalid_Inline_Table);
		skip_ws(r, false);
	}
	tom->type = TOML_Table;
	tom->value.table_v = gros_poisson;
	reader_next(r);
	return (No_Error);
}
