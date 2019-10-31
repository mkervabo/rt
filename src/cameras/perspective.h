/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:18:42 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:13:58 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERAS_PERSPECTIVE_H
# define CAMERAS_PERSPECTIVE_H

# include "camera.h"

struct						s_perspective_camera
{
	struct s_camera	super;
};

struct s_ray				perspective_camera_create_ray(
							struct s_perspective_camera *camera, size_t x,
							size_t y, struct s_size window);
struct s_perspective_camera	*read_perspective_camera(t_toml_table *toml);
void						free_perspective_camera(
							struct s_perspective_camera *camera);
#endif
