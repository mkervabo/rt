#ifndef CAMERAS_360_H
# define CAMERAS_360_H

# include "camera.h"

struct s_360_camera {
	struct s_camera	super;
};

struct s_ray	s_360_camera_create_ray(struct s_360_camera *camera, size_t x, size_t y,
			struct s_size window);
struct s_360_camera	*read_360_camera(t_toml_table *toml);

#endif
