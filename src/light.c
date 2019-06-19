/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:37:58 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/19 14:21:01 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		receive_light(t_light *light, t_vec3 p, t_object *objects[],
	size_t size)
{
	t_ray		shadow;
	t_vec3		to_light;
	t_vec3		direction;
	double		dist;
	t_hit_info	hit;

	to_light = vec3_sub(light->pos, p);
	dist = vec3_length(to_light);
	direction = vec3_divv(to_light, dist);
	shadow = (t_ray) {
		.origin = p,
		.direction = direction
	};
	hit = in_objects(&shadow, objects, size).hit;
	if (hit.t >= 0 && hit.t <= dist)
		return (-1.0);
	else
		return (dist);
}

t_color		diffuse(t_light *light, t_vec3 n, t_vec3 p)
{
	t_color	color;
	t_vec3	n_light;
	double	i;

	n_light = vec3_unit(vec3_sub(p, light->pos));
	i = vec3_dot(n_light, n) * light->intensity;
	color.r = light->color.r * i;
	color.g = light->color.g * i;
	color.b = light->color.b * i;
	return (color);
}

t_color		specular(t_light *light, t_hit_info hit, t_ray *ray)
{
	t_color	color;
	t_vec3	n_light;
	t_vec3	p;
	t_vec3	r;
	double	i;

	p = vec3_add(ray->origin, vec3_multv(ray->direction, hit.t - 0.1));
	n_light = vec3_unit(vec3_sub(p, light->pos));
	r = vec3_unit(vec3_sub(ray->direction, vec3_multv(hit.n, 2
			* vec3_dot(ray->direction, hit.n))));
	if (light->expose % 2 == 0)
		light->expose += 1;
	i = pow(vec3_dot(n_light, r), light->expose);
	if (i > 0)
		i = 0;
	color.r = light->color.r * i;
	color.g = light->color.g * i;
	color.b = light->color.b * i;
	return (color);
}

t_color		phong(t_light *light, t_hit_info hit, t_ray *ray)
{
	t_color	color;
	t_vec3	p;
	t_vec3	r;
	double	i;
	uint8_t dot;

	p = vec3_add(ray->origin, vec3_multv(ray->direction, hit.t - 0.1));
	r = vec3_unit(vec3_sub(ray->direction, vec3_multv(hit.n, 2
				* vec3_dot(ray->direction, hit.n))));
	i = vec3_dot(vec3_unit(vec3_sub(p, light->pos)), hit.n) * light->intensity;
	if (light->expose % 2 == 0)
		light->expose += 1;
	dot = clamp_rgb(-pow(vec3_dot(vec3_unit(vec3_sub(p, light->pos)), r),
		light->expose) * 255);
	color.r = light->color.r * i - dot;
	color.g = light->color.g * i - dot;
	color.b = light->color.b * i - dot;
	return (color);
}
