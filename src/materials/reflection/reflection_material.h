/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_material.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 21:00:02 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:38:30 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_REFLECTION_MATERIAL_H
# define MATERIALS_REFLECTION_MATERIAL_H

# include "material.h"

struct							s_reflection_material
{
	t_material	super;
	double		reflection;
	double		transparency;
	double		refraction;
	t_material	*color;
};

t_color							reflection(t_scene *scene, struct s_ray ray,
	struct s_hit *hit);
t_color							refraction(t_scene *scene, struct s_ray ray,
	struct s_hit *hit);
t_color							reflection_material_color(
	struct s_reflection_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit);
double							reflection_material_transparency(
	struct s_reflection_material *material, struct s_hit *hit,
	t_material **color);
struct s_reflection_material	*read_reflection_material(t_toml_table *toml);
void							free_reflection_material(
	struct s_reflection_material *material);

#endif
