#ifndef SHAPES_CYLINDER_H
# define SHAPES_CYLINDER_H

# include "shape.h"

struct s_cylinder {
	t_shape super;
	double  r;
};

struct s_hit		hit_cylinder(struct s_ray ray, struct s_cylinder *cylinder, struct s_intersection **intersections);
struct s_cylinder	*read_cylinder(t_toml_table *toml);

#endif
