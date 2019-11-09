/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:21:45 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/11/09 14:48:15 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_TYPE_H
# define MATERIAL_TYPE_H

#include "material.h"

enum	e_material_type {
	MATERIAL_NORMAL,
	MATERIAL_UV,
	MATERIAL_MOVE_UV,
	MATERIAL_ZOOM_UV,
	MATERIAL_TEXTURE,
	MATERIAL_COLOR,
	MATERIAL_CHECKERBOARD,
	MATERIAL_VORONOI,
	MATERIAL_DIFFUSE,
	MATERIAL_HEIGHT_MAP,
	MATERIAL_CARTOON,
	MATERIAL_REFLECTION,
	MATERIAL_PERLIN,
	MATERIAL_MARBLE,
	MATERIAL_CLOUD,
	MATERIAL_SPECULAR
};

struct	s_material_record {
	const char	*name;
	t_color		(*color)(t_material *, t_scene *, struct s_ray, struct s_hit *);
	t_material	*(*read)(t_toml_table *toml);
};

#endif
