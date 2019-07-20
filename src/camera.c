/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:37:04 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/20 18:06:43 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

struct s_ray	camera_create_ray(struct s_camera *camera, size_t x, size_t y, struct s_size window)
{
	struct s_ray ray;

	ray = (struct s_ray) {
		.origin = camera->position,
		.direction = vec3_unit(vec3(
			((x + 0.5) / window.width - 0.5),
			((y + 0.5) / window.height - 0.5)
				* ((float)window.height / (float)window.width),
			-1
		))
	};
	ray.direction = vec3_rotate(ray.direction, camera->rotation);
	return (ray);
}
