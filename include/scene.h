#ifndef SCENE_H
# define SCENE_H

# include "object.h"
# include "light.h"
# include "camera.h"

typedef struct	s_scene
{
	struct s_object	*objects;
	size_t		objects_size;
	t_light		**lights;
	size_t		lights_size;
	t_camera	*camera;
}				t_scene;

#endif
