/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:30:41 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/08/11 14:51:08 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "toml.h"
# include "ray.h"
# include "math/vec3.h"
# include "math/size.h"
# include <stddef.h>
# include <stdint.h>

typedef struct	s_camera {
	uint8_t type;
	t_vec3	position;
	t_vec3	rotation;
}				t_camera;

struct s_ray	camera_create_ray(struct s_camera *camera, size_t x, size_t y,
			struct s_size window);
t_camera		*read_camera(t_toml_table *toml);

#endif
