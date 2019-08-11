#include "perspective_camera.h"
#include "camera_types.h"
#include "utils.h"
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
		return (NULL);
	if (!read_camera_super(toml, &camera->super))
		return (nfree(camera));
	camera->super.type = CAMERA_PERSPECTIVE;
	return (camera);
}
