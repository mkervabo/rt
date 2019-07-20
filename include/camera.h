/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:30:41 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/07/20 18:06:13 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "ray.h"
# include "math/vec3.h"
# include "math/size.h"
# include <stddef.h>

typedef struct	s_camera {
	t_vec3	position;
	t_vec3	rotation;
}				t_camera;

struct s_ray	camera_create_ray(struct s_camera *camera, size_t x, size_t y,
			struct s_size window);

#endif
