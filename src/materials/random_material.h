/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_material.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:52:03 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:53:37 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_RANDOM_MATERIAL_H
# define MATERIALS_RANDOM_MATERIAL_H

# include "material.h"

struct							s_random_material
{
	t_material	super;
};

t_color							random_material_color(
	struct s_random_material *material, t_scene *scene, struct s_ray ray,
	struct s_hit *hit);
double							random_material_transparency(
	struct s_random_material *material, struct s_hit *hit);
struct s_random_material		*read_random_material(t_toml_table *toml);
void							free_random_material(
	struct s_random_material *material);

#endif
