/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:42:52 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/14 08:54:23 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include "obj_shape.h"
#include "triangle.h"
#include "shape_types.h"
#include "utils.h"
#include "config_utils.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

struct s_hit				hit_obj_shape(struct s_ray ray,
	struct s_obj_shape *obj, struct s_intersection_tab *intersections)
{
	struct s_hit	max;
	struct s_hit	hit;
	size_t			i;

	(void)intersections;
	i = 0;
	max = (struct s_hit) {
		.t = -1.0
	};
	while (i < obj->size)
	{
		hit = hit_triangle(ray, &obj->triangles[i], NULL);
		if (hit.t >= 0 && (max.t < 0 || hit.t <= max.t))
			max = hit;
		i++;
	}
	return (max);
}

static struct s_triangle	read_obj_triangle(t_obj *obj,
	t_obj_triangle *triangle)
{
	struct s_triangle	object;
	struct s_obj_vertex vertex;

	vertex = obj->v.inner[triangle->a.v_index];
	object.v0 = vec3(vertex.x, vertex.y, vertex.z);
	vertex = obj->v.inner[triangle->b.v_index];
	object.v1 = vec3(vertex.x, vertex.y, vertex.z);
	vertex = obj->v.inner[triangle->c.v_index];
	object.v2 = vec3(vertex.x, vertex.y, vertex.z);
	return (object);
}

static bool					read_obj_triangles(t_obj *obj,
	struct s_triangle **objects, size_t *size)
{
	size_t i;
	size_t j;
	size_t k;

	*size = 0;
	i = 0;
	while (i < obj->len)
		*size += obj->inner[i++].faces.len;
	if (!(*objects = malloc(sizeof(**objects) * *size)))
	{
		obj_free(obj);
		return (false);
	}
	k = 0;
	i = 0;
	while (i < obj->len)
	{
		j = 0;
		while (j < obj->inner[i].faces.len)
			(*objects)[k++] =
				read_obj_triangle(obj, &obj->inner[i].faces.inner[j++]);
		i++;
	}
	obj_free(obj);
	return (true);
}

static bool					read_obj_file(t_toml *value, t_obj *obj_model)
{
	int				fd;
	t_obj_error		err;
	t_obj_reader	r;
	char			buffer[4096];

	if ((fd = open(value->value.string_v, O_RDONLY)) < 0)
	{
		perror("rt");
		return (rt_error(NULL, "Open error in obj shape"));
	}
	r = obj_create_reader(fd, buffer, sizeof(buffer));
	if ((err = obj_read(&r, obj_model)) != Obj_No_Error)
	{
		close(fd);
		return ((bool)(rt_error(NULL, "Invalid obj in obj shape")));
	}
	close(fd);
	return (true);
}

struct s_obj_shape			*read_obj_shape(t_toml_table *toml)
{
	struct s_obj_shape	*obj;
	t_toml				*value;
	t_obj				obj_model;

	if (!(obj = malloc(sizeof(*obj))))
		return (rt_error(NULL, "Can not allocate obj shape"));
	if (!read_shape_super(toml, &obj->super))
		return (rt_error(obj, "Invalid shape super in obj shape"));
	if (!read_toml_type(toml, &value, "path", TOML_String))
		return (rt_error(obj, "Missing path in obj shape"));
	if (!read_obj_file(value, &obj_model))
		return (rt_error(obj, "Can not read obj file"));
	if (!read_obj_triangles(&obj_model, &obj->triangles, &obj->size))
		return (rt_error(obj, "Invalid obj triangle in obj shape"));
	obj->super.type = SHAPE_OBJ;
	return (obj);
}
