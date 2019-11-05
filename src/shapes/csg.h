#ifndef SHAPES_CSG_H
# define SHAPES_CSG_H

# include "shape.h"

enum e_csg_op {
	CSG_UNION,
	CSG_DIFFERENCE,
	CSG_INTERSECTION
};

struct s_csg {
	t_shape			super;
	enum e_csg_op	op;
	t_shape			*first;
	t_shape			*second;
};

struct s_hit		hit_csg(struct s_ray ray, struct s_csg *minus, struct s_intersection_tab *intersections);
struct s_csg		*read_csg(t_toml_table *toml, enum e_csg_op op);
void				free_csg(struct s_csg *csg);
#endif
