#ifndef SHAPES_BOX_H
# define SHAPES_BOX_H

# include "shape.h"

struct s_box {
	t_shape	super;
	t_vec3	bounds[2];
};

struct s_hit	hit_box(struct s_ray ray, struct s_box *box, struct s_intersection **intersections);
struct s_box	*read_box(t_toml_table *toml);

#endif
