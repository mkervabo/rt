#include "group.h"
#include "shape_types.h"
#include "utils.h"
#include "math/quadratic.h"
#include "config_utils.h"
#include "object.h"
#include "raytrace.h"
#include <stdlib.h>

#include <math.h>

struct s_hit hit_group(struct s_ray ray, struct s_group *group,
		struct s_intersection_tab *intersections)
{
	return (hit_scene(group->objects, group->objects_size, ray, intersections));
}

struct s_group	*read_group(t_toml_table *toml)
{
	struct s_group	*group;

	if (!(group = malloc(sizeof(*group))))
		return (rt_error(NULL, "Can not allocate group shape"));
	if (!read_shape_super(toml, &group->super))
		return (rt_error(group, "Invalid super in group shape"));
	if (!(group->objects = read_objects(toml, &group->objects_size)))
		return (rt_error(group, "Invalid objects in group shape"));
	group->super.type = SHAPE_GROUP;
	return (group);
}