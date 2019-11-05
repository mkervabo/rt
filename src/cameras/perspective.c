#include "perspective.h"
#include "camera_types.h"
#include "utils.h"
#include "config_utils.h"
#include <stdlib.h>

struct s_ray	perspective_camera_create_ray(struct s_perspective_camera *camera, size_t x, size_t y,
			struct s_size window)
{
	(void)camera;
	return ((struct s_ray) {
			.direction = vec3_unit(vec3(
				((x + 0.5) / window.width - 0.5),
				((y + 0.5) / window.height - 0.5) * ((float)window.height / (float)window.width),
				-1
			))
	});
}

struct s_perspective_camera	*read_perspective_camera(t_toml_table *toml)
{
	struct s_perspective_camera	*camera;

	if (!(camera = malloc(sizeof(*camera))))
		return (rt_error(NULL, "Can not allocate perpective camera"));
	if (!read_camera_super(toml, &camera->super))
		return (rt_error(camera, "Invalid perspective camera"));
	camera->super.type = CAMERA_PERSPECTIVE;
	return (camera);
}

void			free_perspective_camera(struct s_perspective_camera *camera)
{
	free_camera_super(&camera->super);
	free(camera);
}