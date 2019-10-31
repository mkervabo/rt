/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_material.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:35:31 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:44:54 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_DIFFUSE_MATERIAL_H
# define MATERIALS_DIFFUSE_MATERIAL_H

# include "material.h"

struct						s_diffuse_material
{
	t_material	super;
	t_material	*material;
	double		albedo;
};

t_color						diffuse_material_color(
	struct s_diffuse_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit);
double						diffuse_material_transparency(
	struct s_diffuse_material *material, struct s_hit *hit,
	t_material **color);
struct s_diffuse_material	*read_diffuse_material(t_toml_table *toml);
void						free_diffuse_material(
	struct s_diffuse_material *material);

#endif
