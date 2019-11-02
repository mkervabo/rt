#ifndef SHAPES_GROUP_H
# define SHAPES_GROUP_H

# include "shape.h"

struct s_group
{
	t_shape			super;
	struct s_object	*objects;
	size_t			objects_size;
};

struct s_hit	hit_group(struct s_ray ray, struct s_group *group, struct s_intersection_tab *intersections);
struct s_group	*read_group(t_toml_table *toml);

#endif
