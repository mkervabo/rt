#ifndef SHAPES_PARABOLOID_H
# define SHAPES_PARABOLOID_H

# include "shape.h"

struct s_paraboloid {
	t_shape	super;
	double	r;
	double	h;
};

struct s_hit	hit_paraboloid(struct s_ray ray, struct s_paraboloid *paraboloid, struct s_intersection **intersections);
struct s_paraboloid	*read_paraboloid(t_toml_table *toml);

#endif
