#ifndef LIGHTS_UTILS_H
# define LIGHTS_UTILS_H

#include "toml.h"
#include "light.h"

bool	read_light_super(t_toml_table *toml, t_light *light);

#endif
