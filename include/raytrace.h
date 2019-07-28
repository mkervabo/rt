#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "color.h"
# include "scene.h"
# include "ray.h"

t_color raytrace(t_scene *scene, struct s_ray ray);

#endif