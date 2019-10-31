/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:52:44 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:52:41 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perlin_material.h"
#include "noise.h"
#include "color_material.h"
#include "material_types.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "config_utils.h"
#include <math.h>
#include <stdlib.h>

t_color						perlin_material_color(
	struct s_perlin_material *material,
	t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	t_vec3			p;

	p = ray_point_at(&ray, hit->t);
	return (color_multv(
		material_color(material->material, scene, ray, hit),
		(noise(vec3_multv(p, material->size)) + 1) / 2));
}

double						perlin_material_transparency(
	struct s_perlin_material *material, struct s_hit *hit, t_material **color)
{
	return (material_transparency(material->material, hit, color));
}

struct s_perlin_material	*read_perlin_material(t_toml_table *toml)
{
	struct s_perlin_material	*material;
	t_toml						*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate perlin material"));
	if (!(value = table_get(toml, "size")))
		material->size = 10;
	else if (read_digit(value, &material->size) == false)
		return (rt_error(material, "Invalid size in perlin material"));
	if (read_toml_type(toml, &value, "material", TOML_Table) == false)
		return (rt_error(material, "Missing material in perlin material"));
	else if (!(material->material = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid material in perlin material"));
	material->super.type = MATERIAL_PERLIN;
	return (material);
}

void						free_perlin_material(
	struct s_perlin_material *material)
{
	free_material(material->material);
	free(material);
}
