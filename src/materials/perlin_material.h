/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_material.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:53:37 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:52:51 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_PERLIN_MATERIAL_H
# define MATERIALS_PERLIN_MATERIAL_H

# include "material.h"

struct							s_perlin_material
{
	t_material	super;
	double		size;
	t_material	*material;
};

t_color							perlin_material_color(
	struct s_perlin_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit);
double							perlin_material_transparency(
	struct s_perlin_material *material, struct s_hit *hit, t_material **color);
struct s_perlin_material		*read_perlin_material(t_toml_table *toml);
void							free_perlin_material(
	struct s_perlin_material *material);

#endif
