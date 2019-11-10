#include "checkerboard_material.h"
#include "material_types.h"
#include "config_utils.h"
#include <math.h>
#include <stdlib.h>

static bool					checker(double u, double v, double size)
{
	double s;
	double t;

	s = floor(u * size);
	t = floor(v * size);

    	return (fmod(s + t, 2) == 0);
}

t_color							checkerboard_material_color(struct s_checkerboard_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	if (checker(hit->u, hit->v, material->size))
		return (material_color(material->white, scene, ray, hit));
	else
		return (material_color(material->black, scene, ray, hit));
}

double	checkerboard_material_transparency(struct s_checkerboard_material *material, struct s_hit *hit, t_material **color)
{
	if (checker(hit->u, hit->v, material->size))
		return (material_transparency(material->white, hit, color));
	else
		return (material_transparency(material->black, hit, color));
}

struct s_checkerboard_material	*read_checkerboard_material(t_toml_table *toml)
{
	struct s_checkerboard_material	*material;
	t_toml							*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate checkerboard material"));
	if (!(value = table_get(toml, "size")))
		material->size = 1;
	else if (read_digit(value, &material->size) == false)
		return (rt_error(material, "Invalid size in checkerboard material"));
	if (read_toml_type(toml, &value, "black", TOML_Table) == false)
		return (rt_error(material, "Missing black in checkerboard material"));
	else if (!(material->black = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid black in checkerboard material"));
	if (read_toml_type(toml, &value, "white", TOML_Table) == false)
		return (rt_error(material, "Missing white in checkerboard material"));
	else if (!(material->white = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid white in checkerboard material"));
	material->super.type = MATERIAL_CHECKERBOARD;
	return (material);
}
