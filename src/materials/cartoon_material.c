/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:59:02 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/13 19:33:17 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cartoon_material.h"
#include "material_types.h"
#include "config_utils.h"
#include "material.h"

#include <stdlib.h>
#include <math.h>

static	double				cartoon_intensity(double intensity)
{
	if (intensity <= 0.01)
		intensity = 0;
	else if (intensity <= 0.2)
		intensity = 0.4;
	else if (intensity <= 0.6)
		intensity = 0.6;
	else
		intensity = 1;
	return (intensity);
}

static t_color				cartoon_light_color(
	struct s_cartoon_material *material, void *ctx[3], t_vec3 point,
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
	else if ((value = receive_light(
		(t_scene *)ctx[0], &lray, point, &color)) != 0)
		intensity = fmin(material->albedo / M_PI
				* fmax(vec3_dot(vec3_multv(lray.direction, -1), hit->normal), 0)
				* light->intensity * value * light_decay(lray.origin, point,
					light->decay), 1);
	else
		intensity = 0;
	return (color_multv(
			color_ratio(light->color, color),
			cartoon_intensity(intensity)));
}

t_color						cartoon_material_color(
	struct s_cartoon_material *material, t_scene *scene, struct s_ray ray,
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
		light_color = color_add(light_color, cartoon_light_color(material,
				(void *[3]) { scene, scene->lights[i], &ray }, point, hit));
		i++;
	}
	return (color_ratio(
		material_color(material->material, scene, ray, hit),
		light_color));
}

double						cartoon_material_transparency(
	struct s_cartoon_material *material,
	struct s_hit *hit, t_material **color)
{
	return (material_transparency(material->material, hit, color));
}

struct s_cartoon_material	*read_cartoon_material(t_toml_table *toml)
{
	struct s_cartoon_material	*material;
	t_toml						*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate cartoon material"));
	if (!(value = table_get(toml, "albedo")))
		return (rt_error(material, "Missing albedo in cartoon material"));
	if (!read_digit(value, &material->albedo))
		return (rt_error(material, "Invalid albedo in cartoon material"));
	if (!read_toml_type(toml, &value, "material", TOML_Table))
		return (rt_error(material, "Missing material in cartoon material"));
	if (!(material->material = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid material in cartoon material"));
	material->super.type = MATERIAL_CARTOON;
	return (material);
}
