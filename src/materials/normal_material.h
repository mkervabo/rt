/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:23:33 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/07/20 17:19:37 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_NORMAL_MATERIAL_H
# define MATERIALS_NORMAL_MATERIAL_H

# include "material.h"

struct s_normal_material {
	t_material	super;
};

t_color						normal_material_color(struct s_normal_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_normal_material	*read_normal_material(t_toml_table *toml);

#endif
