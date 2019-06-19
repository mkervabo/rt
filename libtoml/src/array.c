/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:09:19 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/28 11:18:33 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.h"

static t_toml_error	read_array_box(t_reader *r, t_toml *tom,
	t_toml_array *array)
{
	t_toml_error	err;

	if ((err = read_toml_value(r, tom)) != No_Error)
		return (err);
	if (!append_array(array, *tom))
		return (Error_Malloc);
	if (array->inner[array->len - 1].type != array->inner[0].type)
		return (Invalid_Array);
	skip_ws(r, true);
	if (reader_peek(r) == ',')
		reader_next(r);
	else if (reader_peek(r) != ']')
		return (Invalid_Array);
	skip_ws(r, true);
	return (No_Error);
}

t_toml_error		read_array(t_reader *r, t_toml *tom)
{
	t_toml_array	*array;
	t_toml_error	err;

	if (!(array = create_array(10)))
		return (Error_Malloc);
	reader_next(r);
	skip_ws(r, true);
	while (reader_peek(r) != -1 && reader_peek(r) != ']')
	{
		if ((err = read_array_box(r, tom, array)) != No_Error)
			return (free_toml_array(array) + err);
	}
	tom->type = TOML_Array;
	tom->value.array_v = array;
	reader_next(r);
	return (No_Error);
}
