/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_material.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:52:01 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/11/13 19:36:15 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "specular_material.h"
#include "raytrace.h"
#include "material_types.h"
#include "config_utils.h"
#include "math/utils.h"

#include <stdlib.h>
#include <math.h>

static t_color					specular_light_color(void *ctx[4], t_vec3 point,
	struct s_ray ray, struct s_hit *hit)
{
	const t_light	*light = ctx[1];
	double			v[2];
	struct s_ray	lray;
	t_vec3			r;
	t_color			color;

	color = (t_color) { 255, 255, 255 };
	lray.depth = ((struct s_ray *)ctx[3])->depth;
	v[0] = 0;
	if (get_light_ray(light, point, &lray)
		&& !vec3_is_zero(lray.direction)
		&& (v[1] = receive_light(
			(t_scene *)ctx[2], &lray, point, &color)) != 0)
	{
		r = vec3_sub(vec3_multv(hit->normal,
				2 * vec3_dot(hit->normal, lray.direction)), lray.direction);
		v[0] = clamp(light->intensity * pow(vec3_dot(
				vec3_multv(ray.direction, -1), r),
				((struct s_specular_material *)ctx[0])->n) * v[1], 0, 1);
	}
	return (color_multv(color_ratio(light->color, color), v[0]));
}

t_color							specular_material_color(
	struct s_specular_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit)
{
	size_t			i;
	t_color			light_color;
	t_vec3			point;

	point = vec3_add(ray_point_at(&ray, hit->t),
		vec3_multv(hit->normal, SHADOW_BIAS));
	light_color = (t_color){ 0, 0, 0 };
	i = 0;
	while (i < scene->lights_size)
	{
		light_color = color_add(light_color, specular_light_color(
			(void *[4]){ material, scene->lights[i], scene, &ray }, point, ray,
				hit));
		i++;
	}
	return (color_add(material_color(material->material, scene, ray, hit),
		color_multv(light_color, material->k)));
}

double							specular_material_transparency(
	struct s_specular_material *material, struct s_hit *hit, t_material **color)
{
	return (material_transparency(material->material, hit, color));
}

struct s_specular_material		*read_specular_material(t_toml_table *toml)
{
	struct s_specular_material	*material;
	t_toml						*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate specular material"));
	if (!(value = table_get(toml, "n")))
		material->n = 2;
	else if (!read_digit(value, &material->n))
		return (rt_error(material, "Invalid n in specular material"));
	if (!(value = table_get(toml, "k")))
		material->k = 1;
	else if (!read_digit(value, &material->k))
		return (rt_error(material, "Invalid k in specular material"));
	if (material->k > 1 || material->k < 0)
		return (rt_error(material, "k not between 0-1 in specular material"));
	if (!read_toml_type(toml, &value, "material", TOML_Table))
		return (rt_error(material, "Missing material in specular material"));
	if (!(material->material = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid material in specular material"));
	material->super.type = MATERIAL_SPECULAR;
	return (material);
}

void							free_specular_material(
	struct s_specular_material *material)
{
	free_material(material->material);
	free(material);
}
