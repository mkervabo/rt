/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_material.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:09:58 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:57:02 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "uv_material.h"
#include "material_types.h"
#include "config_utils.h"
#include <stdlib.h>

t_color					uv_material_color(struct s_uv_material *material,
	t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	(void)material;
	(void)scene;
	(void)ray;
	return ((t_color) {
		.r = hit->u * 255,
		.g = hit->v * 255,
		.b = (1 - hit->u - hit->v) * 255
	});
}

double					uv_material_transparency(struct s_uv_material *material,
	struct s_hit *hit)
{
	(void)material;
	(void)hit;
	return (0.0);
}

struct s_uv_material	*read_uv_material(t_toml_table *toml)
{
	struct s_uv_material	*material;

	(void)toml;
	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate uv material"));
	material->super.type = MATERIAL_UV;
	return (material);
}

void					free_uv_material(struct s_uv_material *material)
{
	free(material);
}
