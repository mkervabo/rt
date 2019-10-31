/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_360.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:11:16 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 13:50:45 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERAS_CAMERA_360_H
# define CAMERAS_CAMERA_360_H

# include "camera.h"

struct				s_360_camera
{
	struct s_camera	super;
};

struct s_ray		s_360_camera_create_ray(struct s_360_camera *camera,
					size_t x, size_t y, struct s_size window);
struct s_360_camera	*read_360_camera(t_toml_table *toml);
void				free_360_camera(struct s_360_camera *camera);

#endif
