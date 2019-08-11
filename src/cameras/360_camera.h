#ifndef CAMERAS_360_CAMERA_H
# define CAMERAS_360_CAMERA_H

# include "camera.h"

struct s_360_camera {
	t_camera	super;
};

struct s_ray	s_360_camera_create_ray(struct s_360_camera *camera, size_t x, size_t y,
			struct s_size window);
struct s_360_camera	*read_360_camera(t_toml_table *toml);

#endif
