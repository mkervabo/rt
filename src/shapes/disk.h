#ifndef SHAPES_DISK_H
# define SHAPES_DISK_H

# include "shape.h"

struct s_disk {
	t_shape	super;
	double	radius;
	double	inner_radius;
	double	angle;
};

struct s_hit	hit_disk(struct s_ray ray, struct s_disk *disk, struct s_intersection_tab *intersections);
struct s_disk	*read_disk(t_toml_table *toml);
void			free_disk(struct s_disk	*disk);

#endif
