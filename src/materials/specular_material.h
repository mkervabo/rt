/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_material.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 19:47:09 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:55:45 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_SPECULAR_MATERIAL_H
# define MATERIALS_SPECULAR_MATERIAL_H

# include "material.h"

struct							s_specular_material {
	t_material	super;
	t_material	*material;
	double		n;
	double		k;
};

t_color							specular_material_color(
	struct s_specular_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit);
double							specular_material_transparency(
	struct s_specular_material *material, struct s_hit *hit,
	t_material **color);
struct s_specular_material		*read_specular_material(t_toml_table *toml);
void							free_specular_material(
	struct s_specular_material *material);

#endif
