#include "box.h"
#include "shape_types.h"
#include "utils.h"
#include "math/vec3.h"
#include "config_utils.h"
#include "debug/assert.h"
#include <stdlib.h>
#include <math.h>

static bool double_cmp(double a, double b, double coef)
{
	return fabs(a - b) < coef;
}

static t_vec3	box_normal(t_vec3 p, t_vec3 a, t_vec3 b)
{
	double	coef;

	coef = 1e-6;
	while (true)
	{
		if (double_cmp(p.x, a.x, coef))
			return (vec3(-1, 0, 0));
		else if (double_cmp(p.x, b.x, coef))
			return (vec3(1, 0, 0));
		else if (double_cmp(p.y, a.y, coef))
			return (vec3(0, -1, 0));
		else if (double_cmp(p.y, b.y, coef))
			return (vec3(0, 1, 0));
		else if (double_cmp(p.z, a.z, coef))
			return (vec3(0, 0, -1));
		else if (double_cmp(p.z, b.z, coef))
			return (vec3(0, 0, 1));
		coef *= 10;
	}
}

static void		box_uvs(double *u, double *v, t_vec3 normal, t_vec3 dir)
{
	if (normal.x > 0)
	{
		*u = 0.5 - (dir.z / (2 * dir.x));
		*v = 0.5 - (dir.y / (2 * dir.x));
	}
	else if (normal.x < 0)
	{
		*u = 0.5 - (dir.z / (2 * dir.x));
		*v = 0.5 + (dir.y / (2 * dir.x));
	}
	else if (normal.y > 0)
	{
		*u = 0.5 + (dir.x / (2 * dir.y));
		*v = 0.5 + (dir.z / (2 * dir.y));
	}
	else if (normal.y < 0)
	{
		*u = 0.5 - (dir.x / (2 * dir.y));
		*v = 0.5 + (dir.z / (2 * dir.y));
	}
	else if (normal.z > 0)
	{
		*u = 0.5 + (dir.x / (2 * dir.z));
		*v = 0.5 - (dir.y / (2 * dir.z));
	}
	else if (normal.z < 0)
	{
		*u = 0.5 + (dir.x / (2 * dir.z));
		*v = 0.5 + (dir.y / (2 * dir.z));
	}
}

struct s_hit	hit_box(struct s_ray ray, struct s_box *box, struct s_intersection_tab *intersections)
{
	t_vec3	invdir;
	double	min;
	double	max;
	t_vec3	cmin;
	t_vec3	cmax;
	t_vec3	normal;
	double	u;
	double	v;
	t_vec3	p;

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

	if (intersections)
		if ((intersections->inner = malloc(1 * sizeof(struct s_intersection))))
		{
			intersections->len = 1;
			intersections->inner[0] = (struct s_intersection) {
				.from = min, .to = max
			};
		}
	p = ray_point_at(&ray, min);
	normal = box_normal(p, box->bounds[0], box->bounds[1]);
	box_uvs(&u, &v, normal, vec3_unit(p));
	return ((struct s_hit) {
		.t = min,
		.normal = normal,
		.u = u,
		.v = v
	});
}

struct s_box	*read_box(t_toml_table *toml)
{
	struct s_box	*box;
	t_toml			*value;

	if (!(box = malloc(sizeof(*box))))
		return (rt_error(NULL, "Can not allocate box shape"));
	if (!read_shape_super(toml, &box->super))
		return (rt_error(box, "Invalid super in box shape"));
	if (!(read_toml_type(toml, &value, "min", TOML_Table) && read_vec3(value->value.table_v, box->bounds + 0)))
		return (rt_error(box, "Invalid min in box shape"));
	if (!(read_toml_type(toml, &value, "max", TOML_Table) && read_vec3(value->value.table_v, box->bounds + 1)))
		return (rt_error(box, "Invalid max in box shape"));
	box->super.type = SHAPE_BOX;
	return (box);
}

void			free_box(struct s_box *box)
{
	free_shape_super(&box->super);
	free(box);
}