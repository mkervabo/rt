/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marble_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:43:10 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:46:12 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "marble_material.h"
#include "material_types.h"
#include "noise.h"
#include "color.h"
#include "math/vec3.h"
#include "config_utils.h"
#include <math.h>
#include <stdlib.h>

t_color						marble_material_color(
	struct s_marble_material *material, t_scene *scene,
	struct s_ray ray, struct s_hit *hit)
{
	double		x;
	t_vec3		p;

	p = ray_point_at(&ray, hit->t);
	x = sin((p.x * material->size + p.y * material->size + p.z * material->size)
		* turbulence(p));
	x = sqrt(x + 1) * 0.7071;
	x = sqrt(x);
	return (color_multv(material_color(material->material, scene, ray, hit),
		x));
}

double						marble_material_transparency(
	struct s_marble_material *material, struct s_hit *hit, t_material **color)
{
	return (material_transparency(material->material, hit, color));
}

struct s_marble_material	*read_marble_material(t_toml_table *toml)
{
	struct s_marble_material	*material;
	t_toml						*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate marble material"));
	if (!(value = table_get(toml, "size")))
		material->size = 10;
	else if (read_digit(value, &material->size) == false)
		return (rt_error(material, "Invalid size in marble material"));
	if (read_toml_type(toml, &value, "material", TOML_Table) == false)
		return (rt_error(material, "Missing material in marble material"));
	else if (!(material->material = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid material in marble material"));
	material->super.type = MATERIAL_MARBLE;
	return (material);
}

void						free_marble_material(
	struct s_marble_material *material)
{
	free_material(material->material);
	free(material);
}
