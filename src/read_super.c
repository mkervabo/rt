/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_super.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 14:16:01 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/19 14:21:32 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "toml.h"

bool		read_t_vec3(t_toml_table *toml, t_vec3 *vec)
{
	t_toml	*value;

	if (!(value = table_get(toml, "x")))
		vec->x = 0;
	else if (read_digit(value, &vec->x) == false)
		return (false);
	if (!(value = table_get(toml, "y")))
		vec->y = 0;
	else if (read_digit(value, &vec->y) == false)
		return (false);
	if (!(value = table_get(toml, "z")))
		vec->z = 0;
	else if (read_digit(value, &vec->z) == false)
		return (false);
	return (true);
}

static bool	read_super_p_r(t_toml_table *toml, t_object *object)
{
	t_toml		*value;

	if (read_toml_type(toml, &value, "position", TOML_Table))
	{
		if (!read_t_vec3(value->value.table_v, &object->pos))
			return (false);
	}
	else
		object->pos = (t_vec3) {
			0, 0, 0
		};
	if (read_toml_type(toml, &value, "rotation", TOML_Table))
	{
		if (!read_t_vec3(value->value.table_v, &object->rot))
			return (false);
		object->rot = vec3_multv(object->rot, M_PI / 180);
	}
	else
		object->rot = (t_vec3) {
			0, 0, 0
		};
	return (true);
}

bool		read_super(t_toml_table *toml, t_object *object)
{
	t_toml		*value;

	if (!read_super_p_r(toml, object))
		return (false);
	if (read_toml_type(toml, &value, "color", TOML_Table) == false)
		return (false);
	if (!read_color(value->value.table_v, &object->color))
		return (false);
	if (read_toml_type(toml, &value, "light", TOML_String) == false)
		return (false);
	if (!read_light_type(value->value.string_v, &object->light))
		return (false);
	return (true);
}
