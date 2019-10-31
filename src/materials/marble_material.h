/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marble_material.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:45:47 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:46:25 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_MARBLE_MATERIAL_H
# define MATERIALS_MARBLE_MATERIAL_H

# include "material.h"

struct							s_marble_material
{
	t_material	super;
	double		size;
	t_material	*material;
};

t_color							marble_material_color(
	struct s_marble_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit);
double							marble_material_transparency(
	struct s_marble_material *material, struct s_hit *hit,
	t_material **color);
struct s_marble_material		*read_marble_material(t_toml_table *toml);
void							free_marble_material(
	struct s_marble_material *material);

#endif
