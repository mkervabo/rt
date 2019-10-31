/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_uv_material.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:49:50 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:50:55 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_MOVE_UV_MATERIAL_H
# define MATERIALS_MOVE_UV_MATERIAL_H

# include "material.h"

struct						s_move_uv_material
{
	t_material	super;
	double		u;
	double		v;
	t_material	*material;
};

t_color						move_uv_material_color(
	struct s_move_uv_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit);
double						move_uv_material_transparency(
	struct s_move_uv_material *material, struct s_hit *hit, t_material **color);
struct s_move_uv_material	*read_move_uv_material(t_toml_table *toml);
void						free_move_uv_material(
	struct s_move_uv_material *material);
#endif
