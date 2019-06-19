/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:11:55 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/19 14:21:37 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*nfree(void *ptr)
{
	free(ptr);
	return (NULL);
}

bool	read_digit(t_toml *toml, double *digit)
{
	if (toml->type == TOML_Float)
		*digit = toml->value.float_v;
	else if (toml->type == TOML_Integer)
		*digit = toml->value.integer_v;
	else
		return (false);
	return (true);
}

bool	read_toml_type(t_toml_table *toml, t_toml **value, char *name,
	enum e_toml_type type)
{
	if (!(*value = table_get(toml, name)))
		return (false);
	if ((*value)->type != type)
		return (false);
	return (true);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
