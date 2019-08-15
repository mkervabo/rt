#ifndef CAMERAS_PERSPECTIVE_H
# define CAMERAS_PERSPECTIVE_H

# include "camera.h"

struct s_perspective_camera {
	t_camera	super;
};

struct s_ray	perspective_camera_create_ray(struct s_perspective_camera *camera, size_t x, size_t y,
			struct s_size window);
struct s_perspective_camera	*read_perspective_camera(t_toml_table *toml);

#endif
