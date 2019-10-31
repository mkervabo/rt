/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:44:23 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/12 14:50:01 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "toml.h"
# include "shape.h"
# include "color.h"
# include "scene.h"
# include "ray.h"

struct s_scene;
struct s_hit;

typedef struct	s_material
{
	uint8_t	type;
}				t_material;

t_color			material_color(t_material *material, struct s_scene *scene,
	struct s_ray ray, struct s_hit *hit);
t_material		*read_material(t_toml_table *toml);
double			material_transparency(struct s_material *material,
				struct s_hit *hit, t_material **color);
void			free_material(t_material *material);

#endif
