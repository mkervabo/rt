/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:51:40 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:51:47 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normal_material.h"
#include "material_types.h"
#include "config_utils.h"
#include <stdlib.h>

t_color						normal_material_color(
	struct s_normal_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit)
{
	(void)material;
	(void)scene;
	(void)ray;
	return ((t_color) {
		.r = (hit->normal.x + 1) / 2 * 255,
		.g = (hit->normal.y + 1) / 2 * 255,
		.b = (hit->normal.z + 1) / 2 * 255
	});
}

double						normal_material_transparency(
	struct s_normal_material *material, struct s_hit *hit)
{
	(void)material;
	(void)hit;
	return (0.0);
}

struct s_normal_material	*read_normal_material(t_toml_table *toml)
{
	struct s_normal_material	*material;

	(void)toml;
	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate normal material"));
	material->super.type = MATERIAL_NORMAL;
	return (material);
}

void						free_normal_material(
	struct s_normal_material *material)
{
	free(material);
}
