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

struct s_hit		hit_obj_shape(struct s_ray ray, struct s_obj_shape *obj, struct s_intersection_tab *intersections)
{
	struct s_hit	max;
	struct s_hit	hit;
	size_t	i;

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

static t_vec3 vertex_to_vec3(t_obj_vertex *vertex)
{
	return (vec3(vertex->x, vertex->y, vertex->z));
}

static struct s_triangle read_obj_triangle(t_obj_triangle *triangle)
{
	struct s_triangle object;

	object.v0 = vertex_to_vec3(triangle->a.v);
	object.v1 = vertex_to_vec3(triangle->b.v);
	object.v2 = vertex_to_vec3(triangle->c.v);
	//same for uv and normal
	return (object);
}

static bool read_obj_triangles(t_obj *obj, struct s_triangle **objects, size_t *size)
{
	size_t i;
	size_t j;
	size_t k;

	*size = 0;
	i = 0;
	while (i < obj->len)
	{
		*size += obj->inner[i].faces.len;
		i++;
	}
	if (!(*objects = malloc(sizeof(**objects) * *size)))
		return (false);
	k = 0;
	i = 0;
	while (i < obj->len)
	{
		j = 0;
		while (j < obj->inner[i].faces.len)
		{
			(*objects)[k++] = read_obj_triangle(&obj->inner[i].faces.inner[j]);
			j++;
		}
		i++;
	}
	return (true);	
}

struct s_obj_shape	*read_obj_shape(t_toml_table *toml)
{
	struct s_obj_shape		*obj;
	t_toml				*value;
	t_obj_reader			r;
	int				fd;
	t_obj_error			err;
	char				buffer[4096];
	t_obj				obj_model;

	if (!(obj = malloc(sizeof(*obj))))
		return (NULL);
	if (!read_shape_super(toml, &obj->super))
		return (nfree(obj));
	if (!read_toml_type(toml, &value, "path", TOML_String))
		return (nfree(obj));
	if ((fd = open(value->value.string_v, O_RDONLY)) < 0)
	{
		perror("rt");
		return (nfree(obj));
	}
	r = obj_create_reader(fd, buffer, sizeof(buffer));
	if ((err = obj_read(&r, &obj_model)) != Obj_No_Error)
	{
		printf("Read Obj Error %d on %s:%zu:%zu\n", err, value->value.string_v, r.line, r.column);
		close(fd);
		return (nfree(obj)); // TODO(David): print error
	}
	close(fd);
	if (!read_obj_triangles(&obj_model, &obj->triangles, &obj->size))
		return (nfree(obj));
	obj->super.type = SHAPE_OBJ;
	return (obj);
}
