#ifndef SHAPES_TRIANGLE_H
# define SHAPES_TRIANGLE_H

# include "shape.h"

struct s_triangle {
	t_shape	super;
	t_vec3	v0;
	t_vec3	v1;
	t_vec3	v2;
};

struct s_hit		hit_triangle(struct s_ray ray, struct s_triangle *triangle, struct s_intersection_tab *intersections);
struct s_triangle	*read_triangle(t_toml_table *toml);
void				free_triangle(struct s_triangle *triangle);

#endif
