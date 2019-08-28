#ifndef CAMERAS_UTILS_H
# define CAMERAS_UTILS_H

#include "toml.h"
#include "camera.h"

bool	read_camera_super(t_toml_table *toml, struct s_camera *camera);

#endif
