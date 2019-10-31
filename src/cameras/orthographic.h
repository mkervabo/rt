/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orthographic.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:15:46 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:13:48 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERAS_ORTHOGRAPHIC_H
# define CAMERAS_ORTHOGRAPHIC_H

# include "camera.h"

struct							s_orthographic_camera
{
	struct s_camera	super;
};

struct s_ray					orthographic_camera_create_ray(
								struct s_orthographic_camera *camera, size_t x,
								size_t y, struct s_size window);
struct s_orthographic_camera	*read_orthographic_camera(t_toml_table *toml);
void							free_orthographic_camera(
								struct s_orthographic_camera *camera);
#endif
