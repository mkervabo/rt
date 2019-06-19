/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:37:04 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/19 14:20:45 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray	camera_create_ray(t_cam *camera, int x, int y, t_win *window)
{
	t_ray ray;

	ray = (t_ray) {
		.origin = camera->pos,
		.direction = vec3_unit((t_vec3) {
			.x = ((x + 0.5) / window->width - 0.5),
			.y = ((y + 0.5) / window->height - 0.5)
				* ((float)window->height / (float)window->width),
			.z = -1
		})
	};
	ray.direction = vec3_rotate(ray.direction, camera->rot);
	return (ray);
}
