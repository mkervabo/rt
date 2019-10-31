/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_material.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:10:40 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:57:32 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_UV_MATERIAL_H
# define MATERIALS_UV_MATERIAL_H

# include "material.h"

struct					s_uv_material
{
	t_material	super;
};

double					uv_material_transparency(
	struct s_uv_material *material, struct s_hit *hit);
t_color					uv_material_color(struct s_uv_material *material,
	t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_uv_material	*read_uv_material(t_toml_table *toml);
void					free_uv_material(struct s_uv_material *material);

#endif
