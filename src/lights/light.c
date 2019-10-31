/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:24:19 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/13 19:22:48 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "toml.h"
#include "config_utils.h"
#include "string_utils.h"
#include "config.h"

#include "light_types.h"
#include "point_light.h"
#include "ambient_light.h"
#include "directional_light.h"
#include "spot_light.h"

#include <stdlib.h>

bool			get_light_ray(const t_light *light, t_vec3 point,
	struct s_ray *ray)
{
	bool	res;
	size_t	depth;

	depth = ray->depth;
	if (light->type == LIGHT_POINT)
		res = point_get_light_ray(
			(const struct s_point_light *)light, point, ray);
	else if (light->type == LIGHT_AMBIENT)
		res = ambient_get_light_ray(
			(const struct s_ambient_light *)light, point, ray);
	else if (light->type == LIGHT_DIRECTIONAL)
		res = directional_get_light_ray(
			(const struct s_directional_light *)light, point, ray);
	else if (light->type == LIGHT_SPOT)
		res = spot_get_light_ray(
			(const struct s_spot_light *)light, point, ray);
	else
		res = false;
	ray->depth = depth;
	return (res);
}

t_light			*read_light(t_toml_table *toml)
{
	t_toml	*type;

	if (!(type = table_get(toml, "type")))
		return (NULL);
	if (type->type != TOML_String)
		return (NULL);
	if (ft_strcmp(type->value.string_v, "POINT") == 0)
		return ((t_light *)read_point_light(toml));
	else if (ft_strcmp(type->value.string_v, "AMBIENT") == 0)
		return ((t_light *)read_ambient_light(toml));
	else if (ft_strcmp(type->value.string_v, "DIRECTIONAL") == 0)
		return ((t_light *)read_directional_light(toml));
	else if (ft_strcmp(type->value.string_v, "SPOT") == 0)
		return ((t_light *)read_spot_light(toml));
	else
		return (rt_error(NULL, "Invalid light type"));
}

void			free_light(t_light *light)
{
	if (light->type == LIGHT_POINT)
		free_point_light((struct s_point_light *)light);
	else if (light->type == LIGHT_AMBIENT)
		free_ambient_light((struct s_ambient_light *)light);
	else if (light->type == LIGHT_DIRECTIONAL)
		free_directional_light((struct s_directional_light *)light);
	else if (light->type == LIGHT_SPOT)
		free_spot_light((struct s_spot_light *)light);
}

t_light			**read_lights(t_toml_table *toml, size_t *size)
{
	t_light		**lights;
	t_toml		*v;
	size_t		i;

	if (read_toml_type(toml, &v, "lights", TOML_Array))
	{
		if (v->value.array_v->len != 0
			&& v->value.array_v->inner[0].type != TOML_Table)
			return (NULL);
		*size = v->value.array_v->len;
	}
	else
		*size = 0;
	if (!(lights = malloc(sizeof(t_light*) * *size)))
		return (NULL);
	i = 0;
	while (i < *size)
	{
		if (!(lights[i] = read_light(v->value.array_v->inner[i].value.table_v)))
			return ((*size = 0) + free_light_array(lights, i));
		i++;
	}
	return (lights);
}
