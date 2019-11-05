#ifndef SHAPES_CONE_H
# define SHAPES_CONE_H

# include "shape.h"

struct s_cone {
	t_shape	super;
	double	angle;
	bool	revolution;
};

struct s_hit	hit_cone(struct s_ray ray, struct s_cone *sphere, struct s_intersection_tab *intersections);
struct s_cone	*read_cone(t_toml_table *toml);
void			free_cone(struct s_cone *cone);

#endif
