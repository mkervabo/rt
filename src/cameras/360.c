#include "360.h"
#include "camera_types.h"
#include "utils.h"
#include <stdlib.h>
#include <math.h>

struct s_ray	s_360_camera_create_ray(struct s_360_camera *camera, size_t x, size_t y,
			struct s_size window)
{
	(void)camera;
	double phi;
	double lambda;

	phi = -((float)y / (float)window.height - 0.5) * M_PI;
	lambda = ((float)x / (float)window.width - 0.5) * 2 * M_PI;
	return ((struct s_ray) {
			.direction = vec3_rotate(vec3_unit(vec3(
				cos(phi) * cos(lambda),
				cos(phi) * sin(lambda),
				sin(phi)
			)), vec3(M_PI / 2, 0, 0))
	});
}

struct s_360_camera	*read_360_camera(t_toml_table *toml)
{
	struct s_360_camera	*camera;

	if (!(camera = malloc(sizeof(*camera))))
		return (NULL);
	if (!read_camera_super(toml, &camera->super))
		return (nfree(camera));
	camera->super.type = CAMERA_360;
	return (camera);
}
