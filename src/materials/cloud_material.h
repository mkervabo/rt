/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cloud_material.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:31:15 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:43:24 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_CLOUD_MATERIAL_H
# define MATERIALS_CLOUD_MATERIAL_H

# include "material.h"

struct						s_cloud_material
{
	t_material	super;
	double		size[8];
	t_material	*material;
};

t_color						cloud_material_color(
	struct s_cloud_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit);
double						cloud_material_transparency(
	struct s_cloud_material *material, struct s_hit *hit, t_material **color);
struct s_cloud_material		*read_cloud_material(t_toml_table *toml);
void						free_cloud_material(
	struct s_cloud_material *material);

#endif
