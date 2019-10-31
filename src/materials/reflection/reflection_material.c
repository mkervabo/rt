/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_material.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:56:45 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/13 19:26:44 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection_material.h"
#include "config_utils.h"
#include "../material_types.h"
#include "raytrace.h"
#include "math/utils.h"
#include <math.h>
#include <stdlib.h>
#define MAX_DEPTH 5

t_color							reflection(t_scene *scene, struct s_ray ray,
	struct s_hit *hit)
{
	ray.origin = ray_point_at(&ray, hit->t - 0.01);
	ray.direction = vec3_unit(vec3_sub(
		ray.direction,
		vec3_multv(hit->normal, 2 * vec3_dot(hit->normal, ray.direction))));
	return (raytrace(scene, ray, NULL));
}

t_color							reflection_material_color(
	struct s_reflection_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit)
{
	t_color color;
	t_color reflect_color;
	t_color refract_color;

	ray.n2 = material->refraction;
	refract_color = (t_color) { 0, 0, 0 };
	reflect_color = (t_color) { 0, 0, 0 };
	color = material_color(material->color, scene, ray, hit);
	if (material->reflection + material->transparency > 100)
		scale(&material->reflection, &material->transparency, 100);
	color = color_multv(color, (100 - material->transparency
		- material->reflection) / 100.0);
	if (material->reflection > 0 && ray.depth < MAX_DEPTH)
		reflect_color = reflection(scene, ray, hit);
	if (material->refraction > 1.0 && material->transparency > 0
		&& ray.depth < MAX_DEPTH)
		refract_color = refraction(scene, ray, hit);
	reflect_color = color_multv(reflect_color, material->reflection / 100);
	refract_color = color_multv(refract_color, material->transparency / 100);
	color = color_add(color, color_add(reflect_color, refract_color));
	return (color);
}

#define IN_MAT " in reflection material"

struct s_reflection_material	*read_reflection_material(t_toml_table *toml)
{
	struct s_reflection_material	*material;
	t_toml							*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate reflection material"));
	if (!(value = table_get(toml, "reflection")))
		material->reflection = 0;
	else if (!read_digit(value, &material->reflection))
		return (rt_error(material, "Invalid reflection" IN_MAT));
	if (!(value = table_get(toml, "transparency")))
		material->transparency = 0;
	else if (!read_digit(value, &material->transparency))
		return (rt_error(material, "Invalid transparency" IN_MAT));
	if (!(value = table_get(toml, "refraction")))
		material->refraction = 0;
	else if (!read_digit(value, &material->refraction))
		return (rt_error(material, "Invalid refraction" IN_MAT));
	if (read_toml_type(toml, &value, "color", TOML_Table) == false)
		return (rt_error(material, "Missing color" IN_MAT));
	else if (!(material->color = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid color" IN_MAT));
	material->super.type = MATERIAL_REFLECTION;
	return (material);
}

double							reflection_material_transparency(
	struct s_reflection_material *material, struct s_hit *hit,
	t_material **color)
{
	double	value;
	double	value_mat;

	*color = material->color;
	value = material->transparency / 100;
	if ((value_mat = material_transparency(material->color, hit, color)) != 0)
		value *= value_mat;
	return (value);
}

void							free_reflection_material(
	struct s_reflection_material *material)
{
	free(material->color);
	free(material);
}
