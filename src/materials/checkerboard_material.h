/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_material.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:28:28 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:42:37 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_CHECKERBOARD_MATERIAL_H
# define MATERIALS_CHECKERBOARD_MATERIAL_H

# include "material.h"

struct							s_checkerboard_material
{
	t_material	super;
	double		size;
	t_material	*white;
	t_material	*black;
};

t_color							checkerboard_material_color(
	struct s_checkerboard_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit);
double							checkerboard_material_transparency(
	struct s_checkerboard_material *material, struct s_hit *hit,
	t_material **color);
struct s_checkerboard_material	*read_checkerboard_material(t_toml_table *toml);
void							free_checkerboard_material(
	struct s_checkerboard_material *m);

#endif
