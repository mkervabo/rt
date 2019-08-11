#ifndef CAMERAS_UTILS_H
# define CAMERAS_UTILS_H

#include "toml.h"
#include "camera.h"

bool	read_camera_super(t_toml_table *toml, t_camera *camera);

#endif
