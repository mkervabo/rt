/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voronoi_material.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:38:56 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:39:54 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_VORONOI_MATERIAL_H
# define MATERIALS_VORONOI_MATERIAL_H

# include "material.h"
# include "math/vec2.h"

struct						s_voronoi_material
{
	t_material	super;
	double		u;
	double		v;
	double		size;
	t_material	*material;
};

t_vec3						hash3(t_vec2 p);
t_color						voronoi_material_color(
	struct s_voronoi_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit);
double						voronoi_material_transparency(
	struct s_voronoi_material *material, struct s_hit *hit, t_material **color);
struct s_voronoi_material	*read_voronoi_material(t_toml_table *toml);
void						free_voronoi_material(
	struct s_voronoi_material *material);

#endif
