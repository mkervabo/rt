/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 13:02:32 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/12 13:05:11 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.h"
#include <stdlib.h>

static void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*c_src = src;
	char		*c_dst;

	c_dst = dst;
	while (n--)
		*c_dst++ = *c_src++;
	return (dst);
}

bool			append_char(t_str *str, char c)
{
	size_t	new_capacity;
	char	*new;

	if (str->len == str->capacity)
	{
		new_capacity = str->capacity * 2;
		if (!(new = malloc(new_capacity * sizeof(char))))
			return (false);
		ft_memcpy(new, str->inner, str->capacity);
		free(str->inner);
		str->inner = new;
		str->capacity = new_capacity;
	}
	str->inner[str->len++] = c;
	return (true);
}

bool			append_array(t_toml_array *array, t_toml tom)
{
	size_t	new_capacity;
	t_toml	*new;

	if (array->len == array->capacity)
	{
		new_capacity = array->capacity * 2;
		if (!(new = malloc(new_capacity * sizeof(t_toml))))
			return (false);
		ft_memcpy(new, array->inner, array->capacity * sizeof(t_toml));
		free(array->inner);
		array->inner = new;
		array->capacity = new_capacity;
	}
	array->inner[array->len++] = tom;
	return (true);
}

bool			append_table(t_toml_table *table, char *key, t_toml tom)
{
	size_t			new_capacity;
	t_toml_entry	*new;

	if (table->len == table->capacity)
	{
		new_capacity = table->capacity * 2;
		if (!(new = malloc(new_capacity * sizeof(t_toml_entry))))
			return (false);
		ft_memcpy(new, table->inner, table->capacity * sizeof(t_toml_entry));
		free(table->inner);
		table->inner = new;
		table->capacity = new_capacity;
	}
	table->inner[table->len++] = (t_toml_entry) {
		.key = key,
		.value = tom
	};
	return (true);
}
