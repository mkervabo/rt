#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "color.h"
# include "scene.h"
# include "ray.h"
# include "filter.h"

t_color raytrace(t_scene *scene, struct s_ray ray, struct s_pixel_hit *hit);
struct s_hit	hit_scene(t_scene *scene, struct s_ray ray);

#endif
