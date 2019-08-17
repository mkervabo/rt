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
    return (fmod(s + t, 2));
}

t_color							checkerboard_material_color(struct s_checkerboard_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	if (checker(hit->u, hit->v, material->size))
		return (material_color(material->white, scene, ray, hit));
	else
		return (material_color(material->black, scene, ray, hit));
}

struct s_checkerboard_material	*read_checkerboard_material(t_toml_table *toml)
{
	struct s_checkerboard_material	*material;
	t_toml							*value;

	if (!(material = malloc(sizeof(*material))))
		return (NULL);
	if (!(value = table_get(toml, "size")))
		material->size = 1;
	else if (read_digit(value, &material->size) == false)
		return (nfree(material));
	if (read_toml_type(toml, &value, "black", TOML_Table) == false)
		return (nfree(material));
	else if (!(material->black = read_material(value->value.table_v)))
		return (nfree(material));
	if (read_toml_type(toml, &value, "white", TOML_Table) == false)
		return (nfree(material));
	else if (!(material->white = read_material(value->value.table_v)))
		return (nfree(material));
	material->super.type = MATERIAL_CHECKERBOARD;
	return (material);
}
