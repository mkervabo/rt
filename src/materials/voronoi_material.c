#include "voronoi_material.h"
#include "material_types.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "config_utils.h"
#include <math.h>
#include <stdlib.h>

static t_vec3 hash3(t_vec2 p)
{
	t_vec3 q = vec3(
		vec2_dot(p, vec2(127.1, 311.7)), 
		vec2_dot(p, vec2(269.5, 183.3)), 
		vec2_dot(p, vec2(419.2, 371.9))
	);

	q = vec3_multv(vec3(sin(q.x), sin(q.y), sin(q.z)), 43758.5453);
	t_vec3 f = vec3(floor(q.x), floor(q.y), floor(q.z));
	return vec3_sub(q, f);
}

static double clamp(double value, double from, double to)
{
	if (value > to)
		return (to);
	else if (value < from)
		return (from);
	else
		return (value);
}

static double smoothstep(double edge0, double edge1, double x)
{
    x = clamp((x - edge0) / (edge1 - edge0), 0 , 1);
    return (x * x * (3 - 2 * x));
}

double voronoi(t_vec2 x, double u, double v)
{
	t_vec2 p = vec2(floor(x.x), floor(x.y));
	t_vec2 f = vec2_sub(vec2(x.x, x.y), p);

	double k = 1.0 + 63.0 * pow(1.0 - v, 4.0);
	double va = 0.0;
	double wt = 0.0;

	int	i;
	int	j;

	j = -2;
	while (j <= 2)
	{
		i = -2;
		while (i <= 2)
		{
			t_vec2 g = vec2( (double)i, (double)j);
			t_vec3 o = vec3_mult(hash3(vec2_add(p, g)), vec3(u, u, 1.0));
			t_vec2 r = vec2_add(vec2_sub(g, f), vec2(o.x, o.y));
			double d = vec2_dot(r, r);
			double w = pow(1.0 - smoothstep(0.0, 1.414, sqrt(d)), k);
			va += w * o.z;
			wt += w;
			i++;
		}
		j++;
	}
	return (va / wt);
}

t_color						voronoi_material_color(struct s_voronoi_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	double	res;
	t_color color;

	res = voronoi(vec2(hit->u * material->size, hit->v * material->size), material->u, material->v);
	color = material_color(material->material, scene, ray, hit);
	return ((t_color) {
		.r = color.r * res,
		.g = color.g * res,
		.b = color.b * res
	});

}

struct s_voronoi_material	*read_voronoi_material(t_toml_table *toml)
{
	struct s_voronoi_material	*material;
	t_toml						*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate texture material"));
	if (!(value = table_get(toml, "size")))
		material->size = 50;
	else if (read_digit(value, &material->size) == false)
		return (rt_error(material, "Invalid size in voronoi material"));
	if (!(value = table_get(toml, "u")))
		material->u= 1;
	else if (read_digit(value, &material->u) == false || material->u < 0 || material->u > 1)
		return (rt_error(material, "Invalid u in voronoi material"));
	if (!(value = table_get(toml, "v")))
		material->v = 0;
	else if (read_digit(value, &material->v) == false || material->v < 0 || material->v > 1)
		return (rt_error(material, "Invalid v in voronoi material"));
	if (read_toml_type(toml, &value, "material", TOML_Table) == false)
		return (rt_error(material, "Missing material in voronoi material"));
	else if (!(material->material = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid material in voronoi material"));
	material->super.type = MATERIAL_VORONOI;
	return (material);
}
