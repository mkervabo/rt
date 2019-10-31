/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:06:04 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:56:30 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_TEXTURE_H
# define MATERIALS_TEXTURE_H

# include "material.h"
# include "image.h"

struct						s_texture
{
	t_material	super;
	t_image		image;
};

double						texture_transparency(
	struct s_texture *material, struct s_hit *hit);
t_color						texture_color(struct s_texture *material,
	t_scene *scene, struct s_ray ray, struct s_hit *hit);
struct s_texture			*read_texture(t_toml_table *toml);
void						free_texture(struct s_texture *material);

#endif
