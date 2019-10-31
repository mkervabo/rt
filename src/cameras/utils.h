/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:19:31 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/02 17:19:31 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERAS_UTILS_H
# define CAMERAS_UTILS_H

# include "toml.h"
# include "camera.h"

bool	read_camera_super(t_toml_table *toml, struct s_camera *camera);
void	free_camera_super(struct s_camera *camera);

#endif
