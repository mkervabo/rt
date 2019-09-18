#include "shape.h"
#include "debug/assert.h"
#include "toml.h"

#include "shape_types.h"
#include "sphere.h"
#include "cylinder.h"
#include "box.h"
#include "triangle.h"
#include "disk.h"
#include "plane.h"
#include "paraboloid.h"
#include "csg.h"
#include "group.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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
	if (shape->type == SHAPE_SPHERE)
		hit = hit_sphere(ray, (struct s_sphere *)shape, intersections);
	else if (shape->type == SHAPE_CYLINDER)
		hit = hit_cylinder(ray, (struct s_cylinder *)shape, intersections);
	else if (shape->type == SHAPE_BOX)
		hit = hit_box(ray, (struct s_box *)shape, intersections);
	else if (shape->type == SHAPE_TRIANGLE)
		hit = hit_triangle(ray, (struct s_triangle *)shape, intersections);
	else if (shape->type == SHAPE_DISK)
		hit = hit_disk(ray, (struct s_disk *)shape, intersections);
	else if (shape->type == SHAPE_PLANE)
		hit = hit_plane(ray, (struct s_plane *)shape, intersections);
	else if (shape->type == SHAPE_PARABOLOID)
		hit = hit_paraboloid(ray, (struct s_paraboloid *)shape, intersections);
	else if (shape->type == SHAPE_CSG)
		hit = hit_csg(ray, (struct s_csg *)shape, intersections);
	else if (shape->type == SHAPE_GROUP)
		hit = hit_group(ray, (struct s_group *)shape, intersections);
	else
		assertf(false, "Unimplemented type: %d", shape->type);

	if (hit.t > 0)
		// Since object is not rotated we need to rotate it's normal
		hit.normal = vec3_rotate(hit.normal, shape->rotation);
	return (hit);
}

#include <unistd.h>
t_shape			*read_shape(t_toml_table *toml)
{
	t_toml	*type;

	if (!(type = table_get(toml, "type")))
		return (NULL);
	if (type->type != TOML_String)
		return (NULL);
	if (ft_strcmp(type->value.string_v, "SPHERE") == 0)
		return ((t_shape *)read_sphere(toml));
	else if (ft_strcmp(type->value.string_v, "CYLINDER") == 0)
		return ((t_shape *)read_cylinder(toml));
	else if (ft_strcmp(type->value.string_v, "BOX") == 0)
		return ((t_shape *)read_box(toml));
	else if (ft_strcmp(type->value.string_v, "TRIANGLE") == 0)
		return ((t_shape *)read_triangle(toml));
	else if (ft_strcmp(type->value.string_v, "DISK") == 0)
		return ((t_shape *)read_disk(toml));
	else if (ft_strcmp(type->value.string_v, "PLANE") == 0)
		return ((t_shape *)read_plane(toml));
	else if (ft_strcmp(type->value.string_v, "PARABOLOID") == 0)
		return ((t_shape *)read_paraboloid(toml));
	else if (ft_strcmp(type->value.string_v, "GROUP") == 0)
		return ((t_shape *)read_group(toml));
	/*else if (ft_strcmp(type->value.string_v, "CONE") == 0)
		return ((t_shape *)read_cone(toml));*/
	else if (ft_strcmp(type->value.string_v, "UNION") == 0)
		return ((t_shape *)read_csg(toml, CSG_UNION));
	else if (ft_strcmp(type->value.string_v, "INTERSECTION") == 0)
		return ((t_shape *)read_csg(toml, CSG_INTERSECTION));
	else if (ft_strcmp(type->value.string_v, "DIFFERENCE") == 0)
		return ((t_shape *)read_csg(toml, CSG_DIFFERENCE));
	else
			return (rt_error(NULL, "Invalid shape type"));
}
