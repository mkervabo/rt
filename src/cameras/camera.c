#include "camera.h"
#include "debug/assert.h"
#include "camera_types.h"
#include "toml.h"
#include "config_utils.h"
#include "string_utils.h"

#include "perspective.h"
#include "360.h"
#include "orthographic.h"

struct s_ray	camera_create_ray(struct s_camera *camera, size_t x, size_t y,
			struct s_size window)
{
	struct s_ray	ray;

	if (camera->type == CAMERA_PERSPECTIVE)
		ray = perspective_camera_create_ray((struct s_perspective_camera *)camera, x, y, window);
	else if (camera->type == CAMERA_360)
		ray = s_360_camera_create_ray((struct s_360_camera *)camera, x, y, window);
	else if (camera->type == CAMERA_ORTHOGRAPHIC)
		ray = orthographic_camera_create_ray((struct s_orthographic_camera *)camera, x, y, window);
	else
		assertf(false, "Unimplemented camera type: %d", camera->type);
	ray.origin = vec3_add(ray.origin, camera->position);
	ray.direction = vec3_rotate(ray.direction, camera->rotation);
	return (ray);
}

struct s_camera			*read_camera(t_toml_table *toml)
{
	t_toml	*type;

	if (!(type = table_get(toml, "type")))
		return (NULL);
	if (type->type != TOML_String)
		return (NULL);
	if (ft_strcmp(type->value.string_v, "PERSPECTIVE") == 0)
		return ((struct s_camera *)read_perspective_camera(toml));
	else if (ft_strcmp(type->value.string_v, "360") == 0)
		return ((struct s_camera *)read_360_camera(toml));
	else if (ft_strcmp(type->value.string_v, "ORTHOGRAPHIC") == 0)
		return ((struct s_camera *)read_orthographic_camera(toml));
	else
		return (rt_error(NULL, "Invalid camera type"));
}

void	free_camera(struct s_camera *camera)
{
	if (camera->type == CAMERA_PERSPECTIVE)
		free_perspective_camera((struct s_perspective_camera *)camera);
	else if (camera->type == CAMERA_360)
		free_360_camera((struct s_360_camera *)camera);
	else if (camera->type == CAMERA_ORTHOGRAPHIC)
		free_orthographic_camera((struct s_orthographic_camera *)camera);
	else
		assertf(false, "Unimplemented camera type: %d", camera->type);
}