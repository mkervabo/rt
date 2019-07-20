#ifndef SCENE_H
# define SCENE_H

# include "shapes.h"
# include "lights.h"
# include "camera.h"

typedef struct	s_scene
{
	t_shape		**objects;
	size_t		objects_size;
	t_light		**lights;
	size_t		lights_size;
	t_camera	camera;
}				t_scene;

#endif
