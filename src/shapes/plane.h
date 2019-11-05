#ifndef SHAPES_PLANE_H
# define SHAPES_PLANE_H

# include "shape.h"

struct s_plane {
	t_shape	super;
};

struct s_hit	hit_plane(struct s_ray ray, struct s_plane *plane, struct s_intersection_tab *intersections);
struct s_plane	*read_plane(t_toml_table *toml);
void			free_plane(struct s_plane *plane);

#endif
