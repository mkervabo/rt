/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:21:45 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/09/18 18:54:44 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_TYPE_H
# define MATERIAL_TYPE_H

enum e_material_type {
	MATERIAL_NORMAL,
	MATERIAL_UV,
	MATERIAL_TEXTURE,
	MATERIAL_COLOR,
	MATERIAL_CHECKERBOARD,
	MATERIAL_VORONOI,
	MATERIAL_DIFFUSE,
	MATERIAL_HEIGHT_MAP,
	MATERIAL_CARTOON
};

#endif
