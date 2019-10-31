/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 20:20:15 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 18:02:22 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "box.h"
#include "../shape_types.h"
#include "../utils.h"
#include "math/vec3.h"
#include "config_utils.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

static bool		finds_intersections(t_vec3 cmin, t_vec3 cmax, double *mini,
	double *maxi)
{
	double min;
	double max;

	min = cmin.x;
	max = cmax.x;
	if ((min > cmax.y) || (cmin.y > max))
		return (false);
	if (cmin.y > min)
		min = cmin.y;
	if (cmax.y < max)
		max = cmax.y;
	if ((min > cmax.z) || (cmin.z > max))
		return (false);
	if (cmin.z > min)
		min = cmin.z;
	if (cmax.z < max)
		max = cmax.z;
	*mini = min;
	*maxi = max;
	return (true);
}

struct s_hit	hit_box(struct s_ray ray, struct s_box *box,
	struct s_intersection_tab *intersections)
{
	t_vec3	invdir;
	double	min;
	double	max;
	t_vec3	cmin;
	t_vec3	cmax;

	invdir = vec3_invert(ray.direction);
	cmin = vec3(
		(box->bounds[ray.direction.x < 0].x - ray.origin.x) * invdir.x,
		(box->bounds[ray.direction.y < 0].y - ray.origin.y) * invdir.y,
		(box->bounds[ray.direction.z < 0].z - ray.origin.z) * invdir.z);
	cmax = vec3(
		(box->bounds[ray.direction.x >= 0].x - ray.origin.x) * invdir.x,
		(box->bounds[ray.direction.y >= 0].y - ray.origin.y) * invdir.y,
		(box->bounds[ray.direction.z >= 0].z - ray.origin.z) * invdir.z);
	if (!finds_intersections(cmin, cmax, &min, &max))
		return ((struct s_hit) { .t = -1.0 });
	if (intersections)
		if ((intersections->inner = malloc(1 * sizeof(struct s_intersection))))
		{
			intersections->len = 1;
			intersections->inner[0] = (struct s_intersection) {
				.from = min, .to = max };
		}
	return (box_normal_and_uv(min, &ray, box));
}

struct s_box	*read_box(t_toml_table *toml)
{
	struct s_box	*box;
	t_toml			*value;

	if (!(box = malloc(sizeof(*box))))
		return (rt_error(NULL, "Can not allocate box shape"));
	if (!read_shape_super(toml, &box->super))
		return (rt_error(box, "Invalid super in box shape"));
	if (!(read_toml_type(toml, &value, "min", TOML_Table)
		&& read_vec3(value->value.table_v, box->bounds + 0)))
		return (rt_error(box, "Invalid min in box shape"));
	if (!(read_toml_type(toml, &value, "max", TOML_Table)
		&& read_vec3(value->value.table_v, box->bounds + 1)))
		return (rt_error(box, "Invalid max in box shape"));
	box->super.type = SHAPE_BOX;
	return (box);
}

void			free_box(struct s_box *box)
{
	free_shape_super(&box->super);
	free(box);
}
