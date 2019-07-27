/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:04:32 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/07/20 17:27:12 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normal_material.h"
#include "material_types.h"
#include <stdlib.h>

t_color						normal_material_color(struct s_normal_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	return ((t_color) {
		.r = (hit->normal.x + 1) / 2 * 255,
		.g = (hit->normal.y + 1) / 2 * 255,
		.b = (hit->normal.z + 1) / 2 * 255
	});

}

struct s_normal_material	*read_normal_material(t_toml_table *toml)
{
	struct s_normal_material	*material;

	if (!(material = malloc(sizeof(*material))))
		return (NULL);
	material->super.type = MATERIAL_NORMAL;
	return (material);
}
