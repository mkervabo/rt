/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:14:16 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/19 14:21:21 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	read_light_type(char *light, enum e_light_type *type)
{
	if (ft_strcmp(light, "DIFFUSE") == 0)
		*type = Light_Diffuse;
	else if (ft_strcmp(light, "PHONG") == 0)
		*type = Light_Phong;
	else
		return (false);
	return (true);
}

bool	read_color(t_toml_table *toml, t_color *color)
{
	t_toml	*value;

	if (!(value = table_get(toml, "r")))
		color->r = 0;
	if (value->type != TOML_Integer)
		return (false);
	color->r = value->value.integer_v;
	if (!(value = table_get(toml, "g")))
		color->g = 0;
	if (value->type != TOML_Integer)
		return (false);
	color->g = value->value.integer_v;
	if (!(value = table_get(toml, "b")))
		color->r = 0;
	if (value->type != TOML_Integer)
		return (false);
	color->b = value->value.integer_v;
	return (true);
}

t_light	*read_light(t_toml_table *toml)
{
	t_toml	*type;
	t_light	*light;
	double	expose;

	if (!(light = malloc(sizeof(t_light))))
		return (NULL);
	if (read_toml_type(toml, &type, "position", TOML_Table) == false)
		return (nfree(light));
	if (!read_t_vec3(type->value.table_v, &light->pos))
		return (nfree(light));
	if (read_toml_type(toml, &type, "color", TOML_Table) == false)
		return (nfree(light));
	if (!read_color(type->value.table_v, &light->color))
		return (nfree(light));
	if (!(type = table_get(toml, "intensity")))
		return (nfree(light));
	if (read_digit(type, &light->intensity) == false)
		return (nfree(light));
	if (!(type = table_get(toml, "expose")))
		return (nfree(light));
	if (read_digit(type, &expose) == false)
		return (nfree(light));
	light->expose = expose;
	return (light);
}
