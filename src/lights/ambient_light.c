/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:19:59 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:30:23 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ambient_light.h"
#include "light_types.h"
#include "utils.h"
#include "config_utils.h"
#include <stdlib.h>

bool					ambient_get_light_ray(
	const struct s_ambient_light *light, t_vec3 point, struct s_ray *ray)
{
	(void)light;
	(void)point;
	*ray = (struct s_ray) { .depth = 0 };
	return (true);
}

struct s_ambient_light	*read_ambient_light(t_toml_table *toml)
{
	struct s_ambient_light	*light;

	if (!(light = malloc(sizeof(*light))))
		return (rt_error(NULL, "Can not allocate ambient light"));
	if (!read_light_super(toml, &light->super))
		return (rt_error(light, "Invalid ambient light"));
	light->super.type = LIGHT_AMBIENT;
	return (light);
}

void					free_ambient_light(struct s_ambient_light *light)
{
	free_light_super(&light->super);
	free(light);
}
