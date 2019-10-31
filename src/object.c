/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:04:44 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 16:16:58 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "config_utils.h"
#include "config.h"
#include "shapes/shape_types.h"

#include <stdlib.h>

bool		read_object(t_object *obj, t_toml_table *toml)
{
	t_toml	*value;

	if (!(obj->shape = read_shape(toml)))
		return (false);
	if (obj->shape->type != SHAPE_GROUP)
	{
		if (!read_toml_type(toml, &value, "material", TOML_Table))
		{
			free_shape(obj->shape);
			return (false);
		}
		if (!(obj->material = read_material(value->value.table_v)))
		{
			free_shape(obj->shape);
			return (false);
		}
	}
	return (true);
}

t_object	*read_objects(t_toml_table *toml, size_t *size)
{
	t_object		*objs;
	t_toml			*v;
	size_t			i;

	if (read_toml_type(toml, &v, "objects", TOML_Array) == false)
		return (NULL);
	if (v->value.array_v->len == 0
		|| v->value.array_v->inner[0].type != TOML_Table)
		return (NULL);
	*size = v->value.array_v->len;
	if (!(objs = malloc(sizeof(t_object) * *size)))
		return (NULL);
	i = 0;
	while (i < *size)
	{
		if (!read_object(objs + i, v->value.array_v->inner[i].value.table_v))
			return ((*size = 0) + free_object_array(objs, i));
		i++;
	}
	return (objs);
}
