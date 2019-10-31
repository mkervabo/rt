/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:52:34 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/12 14:46:07 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xor_material.h"
#include "../material_types.h"
#include "config_utils.h"

#include <stdlib.h>
#include <math.h>

static t_color				hsv_to_rgb(uint8_t h, uint8_t s, uint8_t v)
{
	uint8_t region;
	uint8_t remainder;
	uint8_t p;
	uint8_t q;
	uint8_t t;

	region = h / 43;
	remainder = (h - (region * 43)) * 6;
	p = (v * (255 - s)) >> 8;
	q = (v * (255 - ((s * remainder) >> 8))) >> 8;
	t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;
	if (region == 0)
		return ((t_color){v, t, p });
	if (region == 1)
		return ((t_color){ q, v, p });
	if (region == 2)
		return ((t_color){ p, v, t });
	if (region == 3)
		return ((t_color){ p, q, v });
	if (region == 4)
		return ((t_color){ t, p, v });
	else
		return ((t_color){ v, p, q });
}

static t_color				xor_hsv(struct s_hit *hit)
{
	uint8_t c;

	c = (uint8_t)(hit->u * 255) ^ (uint8_t)(hit->v * 255);
	return (hsv_to_rgb(c, 255, 255));
}

static t_color				xor_rgb(struct s_hit *hit)
{
	uint8_t c;

	c = (uint8_t)(hit->u * 255) ^ (uint8_t)(hit->v * 255);
	return ((t_color) {c, c, c});
}

t_color						xor_material_color(struct s_xor_material *material,
	t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	(void)scene;
	(void)ray;
	if (material->color)
		return (xor_hsv(hit));
	return (xor_rgb(hit));
}

struct s_xor_material		*read_xor_material(t_toml_table *toml)
{
	struct s_xor_material	*material;
	t_toml					*value;

	(void)toml;
	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate xor material"));
	if (!read_toml_type(toml, &value, "color", TOML_Boolean))
		material->color = true;
	material->super.type = MATERIAL_XOR;
	return (material);
}
