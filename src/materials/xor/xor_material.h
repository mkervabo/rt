/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_material.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:56:05 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 16:25:25 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_XOR_MATERIAL_H
# define MATERIALS_XOR_MATERIAL_H

# include "material.h"
# include <stdbool.h>

struct						s_xor_material
{
	t_material	super;
	bool		color;
};

double						xor_material_transparency(
	struct s_xor_material *material, struct s_hit *hit);
t_color						xor_material_color(struct s_xor_material *material,
	t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_xor_material		*read_xor_material(t_toml_table *toml);
void						free_xor_material(struct s_xor_material *material);

#endif
