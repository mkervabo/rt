#include "shape.h"
#include "debug/assert.h"
#include "toml.h"
#include "config_utils.h"
#include "string_utils.h"

#include <math.h>

#include "shape_types.h"
#include "sphere.h"
#include "cylinder.h"
#include "cone.h"
#include "plane.h"
#include "box.h"
#include "triangle.h"
#include "disk.h"
#include "paraboloid.h"
#include "csg.h"
#include "group.h"
#include "obj_shape.h"


static struct s_shape_record g_shapes[] = {
	[SHAPE_SPHERE] = { "SPHERE", (void *)hit_sphere, (void *)read_sphere, (void *)free_sphere },
	[SHAPE_CYLINDER] = { "CYLINDER", (void *)hit_cylinder, (void *)read_cylinder, (void *)free_cylinder },
	[SHAPE_CONE] = { "CONE", (void *)hit_cone, (void *)read_cone, (void *)free_cone },
	[SHAPE_PLANE] = { "PLANE", (void *)hit_plane, (void *)read_plane, (void *)free_plane },
	[SHAPE_BOX] = { "BOX", (void *)hit_box, (void *)read_box, (void *)free_box },
	[SHAPE_TRIANGLE] = { "TRIANGLE", (void *)hit_triangle, (void *)read_triangle, (void *)free_triangle },
	[SHAPE_DISK] = { "DISK", (void *)hit_disk, (void *)read_disk,  (void *)free_disk},
	[SHAPE_PARABOLOID] = { "PARABOLOID", (void *)hit_paraboloid, (void *)read_paraboloid, (void *)free_paraboloid },
	[SHAPE_CSG] = { NULL, (void *)hit_csg, NULL, (void *)free_csg }, // Custom read
	[SHAPE_GROUP] = { "GROUP", (void *)hit_group, (void *)read_group, (void *)free_group },
	[SHAPE_OBJ] = { "OBJ", (void *)hit_obj_shape, (void *)read_obj_shape, (void *)free_obj_shape }
};

struct s_hit	hit_shape(struct s_ray ray, t_shape *shape, struct s_intersection_tab *intersections)
{
	struct s_hit	hit;

	// Move ray at the inverse of it's position and rotate it at the inverse of it's rotation
	// This is the same as moving the object in the scene, but it avoid implementing it for each
	// shapes
	// See http://woo4.me/raytracer/translations/
	ray.origin = vec3_sub(ray.origin, shape->position);
	ray.origin = vec3_rotate(ray.origin, vec3_multv(shape->rotation, -1));
	ray.direction = vec3_rotate(ray.direction, vec3_multv(shape->rotation, -1));
	if (shape->type <= (sizeof(g_shapes) / sizeof(*g_shapes)))
		hit = g_shapes[shape->type].hit(ray, shape, intersections);
	else
	{
		assertf(false, "Unimplemented shape type: %d", shape->type);
		hit = (struct s_hit) { .t = -1 };
	}
	if (hit.t > 0)
	{
		// Since object is not rotated we need to rotate it's normal
		hit.normal = vec3_rotate(hit.normal, shape->rotation);
	}
	return (hit);
}

t_shape			*read_shape(t_toml_table *toml)
{
	t_toml	*type;
	size_t	i;

	if (!(type = table_get(toml, "type")))
		return (NULL);
	if (type->type != TOML_String)
		return (NULL);
	if (ft_strcmp(type->value.string_v, "UNION") == 0)
		return ((t_shape *)read_csg(toml, CSG_UNION));
	else if (ft_strcmp(type->value.string_v, "INTERSECTION") == 0)
		return ((t_shape *)read_csg(toml, CSG_INTERSECTION));
	else if (ft_strcmp(type->value.string_v, "DIFFERENCE") == 0)
		return ((t_shape *)read_csg(toml, CSG_DIFFERENCE));
	i = 0;
	while (i < (sizeof(g_shapes) / sizeof(*g_shapes)))
	{
		if (g_shapes[i].name && ft_strcmp(type->value.string_v, g_shapes[i].name) == 0)
			return (g_shapes[i].read(toml));
		i++;
	}
	return (rt_error(NULL, "Invalid shape type"));
}

void	free_shape(t_shape *shape)
{
	if (shape->type <= (sizeof(g_shapes) / sizeof(*g_shapes)))
		g_shapes[shape->type].free(shape);
}
