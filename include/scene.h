/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:39:33 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/05 14:39:38 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "object.h"
# include "light.h"
# include "camera.h"
# include "filter.h"

typedef struct	s_scene
{
	struct s_object	*objects;
	size_t			objects_size;
	t_light			**lights;
	size_t			lights_size;
	t_camera		*camera;
	struct s_filter	**filters;
	size_t			filters_size;
}				t_scene;

#endif
