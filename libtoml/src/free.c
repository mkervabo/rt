/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 10:43:21 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/28 11:12:52 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.h"
#include <stdlib.h>

int		free_toml_table(t_toml_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->len)
	{
		free(table->inner[i].key);
		free_toml(&table->inner[i].value);
		i++;
	}
	free(table->inner);
	free(table);
	return (0);
}

int		free_toml_array(t_toml_array *array)
{
	size_t	i;

	i = 0;
	while (i < array->len)
	{
		free_toml(array->inner + i);
		i++;
	}
	free(array->inner);
	free(array);
	return (0);
}

int		free_toml_string(char *str)
{
	free(str);
	return (0);
}

void	free_toml(t_toml *tom)
{
	if (tom->type == TOML_Table)
		free_toml_table(tom->value.table_v);
	if (tom->type == TOML_Array)
		free_toml_array(tom->value.array_v);
	if (tom->type == TOML_String)
		free_toml_string(tom->value.string_v);
}
