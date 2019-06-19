/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:51:56 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/12 13:04:09 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.h"
#include <stdlib.h>

t_str			create_str(size_t capacity)
{
	return ((t_str) {
		.len = 0,
		.capacity = capacity,
		.inner = malloc(capacity * sizeof(char))
	});
}

t_toml_array	*create_array(size_t capacity)
{
	t_toml_array	*array;
	t_toml			*tom;

	if (!(array = malloc(sizeof(t_toml_array))))
		return (NULL);
	if (!(tom = malloc(capacity * sizeof(t_toml))))
	{
		free(array);
		return (NULL);
	}
	*array = (t_toml_array) {
		.len = 0,
		.capacity = capacity,
		.inner = tom
	};
	return (array);
}

t_toml_table	*create_table(size_t capacity)
{
	t_toml_table	*table;
	t_toml_entry	*tom;

	if (!(table = malloc(sizeof(t_toml_table))))
		return (NULL);
	if (!(tom = malloc(capacity * sizeof(t_toml_entry))))
	{
		free(table);
		return (NULL);
	}
	*table = (t_toml_table) {
		.len = 0,
		.capacity = capacity,
		.inner = tom
	};
	return (table);
}
