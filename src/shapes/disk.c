/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:00:23 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/12 14:02:00 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disk.h"
#include "shape_types.h"
#include "utils.h"
#include "math/quadratic.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>

static struct s_hit	hit_return(double t, double r_hit, double phi,
					struct s_disk *disk)
{
	return ((struct s_hit) {
		.t = t,
		.normal = vec3(0, 0, 1),
		.u = phi / disk->angle,
		.v = (disk->radius - r_hit) / (disk->radius - disk->inner_radius)
	});
}

static void			function(struct s_intersection_tab *intersections, double t)
{
	intersections->len = 1;
	intersections->inner[0] = (struct s_intersection) {
	.from = t, .to = t };
}

struct s_hit		hit_disk(struct s_ray ray, struct s_disk *disk,
					struct s_intersection_tab *intersections)
{
	t_vec3	p;
	double	v[2];
	double	phi;
	double	r_hit;

	if (fabs(ray.direction.z) < 1e-6)
		return ((struct s_hit) { .t = -1.0 });
	v[0] = -ray.origin.z / ray.direction.z;
	if (v[0] < 0)
		return ((struct s_hit) { .t = -1.0 });
	p = ray_point_at(&ray, v[0]);
	v[1] = p.x * p.x + p.y * p.y;
	if (v[1] > disk->radius * disk->radius
		|| v[1] < disk->inner_radius * disk->inner_radius)
		return ((struct s_hit) { .t = -1.0 });
	phi = atan2(p.y, p.x);
	if (phi < 0)
		phi += 2 * M_PI;
	if (phi > disk->angle)
		return ((struct s_hit) { .t = -1.0 });
	r_hit = sqrt(v[1]);
	if (intersections)
		if ((intersections->inner = malloc(1 * sizeof(struct s_intersection))))
			function(intersections, v[0]);
	return (hit_return(v[0], phi, r_hit, disk));
}

struct s_disk		*read_disk(t_toml_table *toml)
{
	struct s_disk	*disk;
	t_toml			*radius;

	if (!(disk = malloc(sizeof(*disk))))
		return (rt_error(NULL, "Can not allocate disk shape"));
	if (!(radius = table_get(toml, "radius")))
		return (rt_error(disk, "Missing radius in disk shape"));
	if (!read_shape_super(toml, &disk->super))
		return (rt_error(disk, "Invalid super in disk shape"));
	if (read_digit(radius, &disk->radius) == false)
		return (rt_error(disk, "Invalid radius in disk shape"));
	if (!(radius = table_get(toml, "inner_radius")))
		disk->inner_radius = 0;
	else if (read_digit(radius, &disk->inner_radius) == false)
		return (rt_error(disk, "Missing inner radius in disk shape"));
	if (!(radius = table_get(toml, "angle")))
		disk->angle = 360;
	else if (read_digit(radius, &disk->angle) == false)
		return (rt_error(disk, "Missing angle in disk shape"));
	disk->angle *= M_PI / 180;
	disk->super.type = SHAPE_DISK;
	return (disk);
}

void				free_disk(struct s_disk	*disk)
{
	free_shape_super(&disk->super);
	free(disk);
}
