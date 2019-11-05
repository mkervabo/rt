#include "orthographic.h"
#include "camera_types.h"
#include "utils.h"
#include "config_utils.h"
#include <stdlib.h>

struct s_ray	orthographic_camera_create_ray(struct s_orthographic_camera *camera, size_t x, size_t y,
			struct s_size window)
{
	(void)camera;
	return ((struct s_ray) {
			.origin = vec3(
				((x + 0.5) / window.width - 0.5),
				((y + 0.5) / window.height - 0.5) * ((float)window.height / (float)window.width),
				0
			),
			.direction = vec3(0, 0, -1)
	});
}

struct s_orthographic_camera	*read_orthographic_camera(t_toml_table *toml)
{
	struct s_orthographic_camera	*camera;

	if (!(camera = malloc(sizeof(*camera))))
		return (rt_error(NULL, "Can not allocate orthographic camera"));
	if (!read_camera_super(toml, &camera->super))
		return (rt_error(camera, "Invalid orthographic camera"));
	camera->super.type = CAMERA_ORTHOGRAPHIC;
	return (camera);
}

void			free_orthographic_camera(struct s_orthographic_camera *camera)
{
	free_camera_super(&camera->super);
	free(camera);
}
