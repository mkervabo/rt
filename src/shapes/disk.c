#include "disk.h"
#include "shape_types.h"
#include "utils.h"
#include "math/quadratic.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>

struct s_hit hit_disk(struct s_ray ray, struct s_disk *disk,
		struct s_intersection_tab *intersections)
{
	if (fabs(ray.direction.z) < 1e-6)
		return ((struct s_hit) { .t = -1.0 });

	double t = -ray.origin.z / ray.direction.z;

	if (t < 0)
		return ((struct s_hit) { .t = -1.0 });

	t_vec3 p = ray_point_at(&ray, t);

	double dist = p.x * p.x + p.y * p.y;

	if (dist > disk->radius * disk->radius
			|| dist < disk->inner_radius * disk->inner_radius)
		return ((struct s_hit) { .t = -1.0 });

	double phi = atan2(p.y, p.x);
	if (phi < 0)
		phi += 2 * M_PI;
	if (phi > disk->angle)
		return ((struct s_hit) { .t = -1.0 });

	double r_hit = sqrt(dist);

	return ((struct s_hit) {
		.t = t,
		.normal = vec3(0, 0, 1),
		.u = phi / disk->angle,
		.v = (disk->radius - r_hit) / (disk->radius - disk->inner_radius)
	});
}

struct s_disk	*read_disk(t_toml_table *toml)
{
	struct s_disk	*disk;
	t_toml			*radius;

	if (!(disk = malloc(sizeof(*disk))))
		return (rt_error(NULL, "Can not allocate disk shape"));
	if (!(radius = table_get(toml, "radius")))
		return (rt_error(disk, "Missing radius in disk shape"));
	if (!read_shape_super(toml, &disk->super))
		return (rt_error(disk, "Invalid super in disk shape"));
	if (read_digit(radius, &disk->radius) == false)
		return (rt_error(disk, "Invalid radius in disk shape"));
	if (!(radius = table_get(toml, "inner_radius")))
		disk->inner_radius = 0;
	else if (read_digit(radius, &disk->inner_radius) == false)
		return (rt_error(disk, "Missing inner radius in disk shape"));
	if (!(radius = table_get(toml, "angle")))
		disk->angle = 360;
	else if (read_digit(radius, &disk->angle) == false)
		return (rt_error(disk, "Missing angle in disk shape"));
	disk->angle *= M_PI / 180;
	disk->super.type = SHAPE_DISK;
	return (disk);
}
