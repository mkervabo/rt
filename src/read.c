/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:39:51 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/19 14:21:41 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "toml.h"

bool		read_window(t_toml_table *toml, t_win *win)
{
	t_toml	*value;
	double	width;
	double	height;

	if (!(value = table_get(toml, "width")))
		return (false);
	if (!read_digit(value, &width))
		return (false);
	win->width = width;
	if (!(value = table_get(toml, "height")))
		return (false);
	if (!read_digit(value, &height))
		return (false);
	win->height = height;
	if (!(read_toml_type(toml, &value, "name", TOML_String)))
		return (false);
	win->name = value->value.string_v;
	value->value.string_v = NULL;
	return (true);
}

t_light		**read_lights(t_toml_table *toml, size_t *size)
{
	t_light		**lights;
	t_toml		*v;
	size_t		i;

	if (read_toml_type(toml, &v, "lights", TOML_Array) == false)
		return (NULL);
	if (v->value.array_v->len == 0
		|| v->value.array_v->inner[0].type != TOML_Table)
		return (NULL);
	*size = v->value.array_v->len;
	if (!(lights = malloc(sizeof(t_light*) * *size)))
		return (NULL);
	i = 0;
	while (i < *size)
	{
		if (!(lights[i] = read_light(v->value.array_v->inner[i].value.table_v)))
			return (free_ptr_array((void **)lights, i));
		i++;
	}
	return (lights);
}

t_object	**read_objects(t_toml_table *toml, size_t *size)
{
	t_object		**objs;
	t_toml			*v;
	size_t			i;

	if (read_toml_type(toml, &v, "objects", TOML_Array) == false)
		return (NULL);
	if (v->value.array_v->len == 0
		|| v->value.array_v->inner[0].type != TOML_Table)
		return (NULL);
	*size = v->value.array_v->len;
	if (!(objs = malloc(sizeof(t_object*) * *size)))
		return (NULL);
	i = 0;
	while (i < *size)
	{
		if (!(objs[i] = read_object(v->value.array_v->inner[i].value.table_v)))
			return (free_ptr_array((void **)objs, i));
		i++;
	}
	return (objs);
}

bool		read_camera(t_toml_table *toml, t_cam *cam)
{
	t_toml	*camera;
	t_toml	*value;

	if (!read_toml_type(toml, &camera, "camera", TOML_Table))
		return (false);
	if (!read_toml_type(camera->value.table_v, &value, "position", TOML_Table))
		return (false);
	if (!read_t_vec3(value->value.table_v, &cam->pos))
		return (false);
	if (!read_toml_type(camera->value.table_v, &value, "rotation", TOML_Table))
		return (false);
	if (!read_t_vec3(value->value.table_v, &cam->rot))
		return (false);
	cam->rot = vec3_multv(cam->rot, M_PI / 180);
	return (true);
}
