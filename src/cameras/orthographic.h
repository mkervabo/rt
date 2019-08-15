#ifndef CAMERAS_ORTHOGRAPHIC_H
# define CAMERAS_ORTHOGRAPHIC_H

# include "camera.h"

struct s_orthographic_camera {
	t_camera	super;
};

struct s_ray	orthographic_camera_create_ray(struct s_orthographic_camera *camera, size_t x, size_t y,
			struct s_size window);
struct s_orthographic_camera	*read_orthographic_camera(t_toml_table *toml);

#endif
