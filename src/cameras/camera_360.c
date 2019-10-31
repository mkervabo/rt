/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_360.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:10:21 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:14:54 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_360.h"
#include "camera_types.h"
#include "config_utils.h"
#include "utils.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>

struct s_ray		s_360_camera_create_ray(struct s_360_camera *camera,
	size_t x, size_t y, struct s_size window)
{
	double phi;
	double lambda;

	(void)camera;
	phi = -((float)y / (float)window.height - 0.5) * M_PI;
	lambda = ((float)x / (float)window.width - 0.5) * 2 * M_PI;
	return ((struct s_ray) {
			.direction = vec3_rotate(vec3_unit(vec3(
				cos(phi) * cos(lambda),
				cos(phi) * sin(lambda),
				sin(phi))),
				vec3(M_PI / 2, 0, 0))
				});
}

struct s_360_camera	*read_360_camera(t_toml_table *toml)
{
	struct s_360_camera	*camera;

	if (!(camera = malloc(sizeof(*camera))))
		return (rt_error(NULL, "Can not allocate 360 camera"));
	if (!read_camera_super(toml, &camera->super))
		return (rt_error(camera, "Invalid 360 camera"));
	camera->super.type = CAMERA_360;
	return (camera);
}

void				free_360_camera(struct s_360_camera *camera)
{
	free_camera_super(&camera->super);
	free(camera);
}
