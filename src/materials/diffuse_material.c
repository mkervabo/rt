/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:33:36 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/13 19:34:11 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "diffuse_material.h"
#include "material_types.h"
#include "config_utils.h"

#include <stdlib.h>
#include <math.h>

static t_color				diffuse_light_color(
	struct s_diffuse_material *material, void *ctx[3], t_vec3 point,
	struct s_hit *hit)
{
	const t_light	*light = ctx[1];
	struct s_ray	lray;
	double			intensity;
	double			value;
	t_color			color;

	lray.depth = ((struct s_ray *)ctx[2])->depth;
	color = (t_color) { 255, 255, 255 };
	if (get_light_ray(light, point, &lray) == false)
		intensity = 0;
	else if (vec3_is_zero(lray.direction))
		intensity = light->intensity;
	else if ((value = receive_light((t_scene *)ctx[0],
			&lray, point, &color)) != 0)
		intensity = fmin(material->albedo / M_PI * fmax(vec3_dot(
			vec3_multv(lray.direction, -1), hit->normal), 0) * light->intensity
			* value * light_decay(lray.origin, point, light->decay), 1);
	else
		intensity = 0;
	return (color_multv(
		color_ratio(light->color, color),
		intensity));
}

t_color						diffuse_material_color(
	struct s_diffuse_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit)
{
	size_t	i;
	t_color	light_color;
	t_vec3	point;

	point = vec3_add(ray_point_at(&ray, hit->t),
		vec3_multv(hit->normal, SHADOW_BIAS));
	light_color = (t_color){ 0, 0, 0 };
	i = 0;
	while (i < scene->lights_size)
	{
		light_color = color_add(light_color, diffuse_light_color(material,
				(void *[3]) { scene, scene->lights[i], &ray }, point, hit));
		i++;
	}
	return (color_ratio(
		material_color(material->material, scene, ray, hit),
		light_color));
}

double						diffuse_material_transparency(
	struct s_diffuse_material *material, struct s_hit *hit, t_material **color)
{
	return (material_transparency(material->material, hit, color));
}

struct s_diffuse_material	*read_diffuse_material(t_toml_table *toml)
{
	struct s_diffuse_material	*material;
	t_toml						*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate color material"));
	if (!(value = table_get(toml, "albedo")))
		return (rt_error(material, "Missing albedo in color material"));
	if (!read_digit(value, &material->albedo))
		return (rt_error(material, "Invalid albedo in color material"));
	if (!read_toml_type(toml, &value, "material", TOML_Table))
		return (rt_error(material, "Missing material in color material"));
	if (!(material->material = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid material in color material"));
	material->super.type = MATERIAL_DIFFUSE;
	return (material);
}

void						free_diffuse_material(
	struct s_diffuse_material *material)
{
	free_material(material->material);
	free(material);
}
