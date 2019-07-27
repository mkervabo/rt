#include "box.h"
#include "shape_types.h"
#include "utils.h"
#include "math/vec3.h"
#include "config_utils.h"
#include <stdlib.h>

static t_vec3	box_normal(double t, t_vec3 min, t_vec3 max)
{
	// TODO
	if (t == min.x)
		return (vec3(1, 0, 0));
	if (t == min.y)
		return (vec3(0, 1, 0));
	if (t == min.z)
		return (vec3(0, 0, 1));
	if (t == max.x)
		return (vec3(-1, 0, 0));
	if (t == max.y)
		return (vec3(0, -1, 0));
	if (t == max.z)
		return (vec3(0, 0, -1));
	
}

struct s_hit	hit_box(struct s_ray ray, struct s_box *box, struct s_intersection **intersections)
{
	t_vec3	invdir;
	double	min;
	double	max;
	t_vec3	cmin;
	t_vec3	cmax;


	invdir = vec3_invert(ray.direction);
	cmin = vec3(
		(box->bounds[ray.direction.x < 0].x - ray.origin.x) * invdir.x,
		(box->bounds[ray.direction.y < 0].y - ray.origin.y) * invdir.y,
		(box->bounds[ray.direction.z < 0].z - ray.origin.z) * invdir.z
	);
	cmax = vec3(
		(box->bounds[ray.direction.x >= 0].x - ray.origin.x) * invdir.x,
		(box->bounds[ray.direction.y >= 0].y - ray.origin.y) * invdir.y,
		(box->bounds[ray.direction.z >= 0].z - ray.origin.z) * invdir.z
	);

	min = cmin.x;
	max = cmax.x;
	if ((min > cmax.y) || (cmin.y > max)) 
		return ((struct s_hit) {
			.t = -1.0,
		});
	if (cmin.y > min) 
		min = cmin.y; 
	if (cmax.y < max) 
		max = cmax.y; 
	if ((min > cmax.z) || (cmin.z > max)) 
		return ((struct s_hit) {
			.t = -1.0,
		});
	if (cmin.z > min) 
		min = cmin.z; 
	if (cmax.z < max) 
		max = cmax.z; 

	return ((struct s_hit) {
		.t = min,
		.normal = box_normal(min, cmin, cmax)
	});
}

struct s_box	*read_box(t_toml_table *toml)
{
	struct s_box	*box;
	t_toml			*value;

	if (!(box = malloc(sizeof(*box))))
		return (NULL);
	if (!read_shape_super(toml, &box->super))
		return (nfree(box));
	if (!(read_toml_type(toml, &value, "min", TOML_Table) && read_vec3(value->value.table_v, box->bounds + 0)))
		return (nfree(box));
	if (!(read_toml_type(toml, &value, "max", TOML_Table) && read_vec3(value->value.table_v, box->bounds + 1)))
		return (nfree(box));
	box->super.type = SHAPE_BOX;
	return (box);
}
