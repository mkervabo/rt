/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_material.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:32:41 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:44:39 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_COLOR_MATERIAL_H
# define MATERIALS_COLOR_MATERIAL_H

# include "material.h"

struct					s_color_material
{
	t_material	super;
	t_color		color;
};

t_color					color_material_color(struct s_color_material *material,
	t_scene *scene, struct s_ray ray, struct s_hit *hit);
double					color_material_transparency(
	struct s_color_material *material);
struct s_color_material	*read_color_material(t_toml_table *toml);
void					free_color_material(struct s_color_material *material);

#endif
