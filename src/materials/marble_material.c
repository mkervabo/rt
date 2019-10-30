#include "marble_material.h"
#include "material_types.h"
#include "noise.h"
#include "color.h"
#include "math/vec3.h"
#include "config_utils.h"
#include <math.h>
#include <stdlib.h>

t_color						marble_material_color(
	struct s_marble_material *material, t_scene *scene,
	struct s_ray ray, struct s_hit *hit)
{
	double		x;
	t_vec3		p;

	p = ray_point_at(&ray, hit->t);
	x = sin((p.x * material->size + p.y * material->size + p.z * material->size) * turbulence(p));
	x = sqrt(x + 1) * 0.7071;
	x = sqrt(x);
	return (color_multv(material_color(material->material, scene, ray, hit), x));

}


struct s_marble_material	*read_marble_material(t_toml_table *toml)
{
	struct s_marble_material	*material;
	t_toml						*value;

	if (!(material = malloc(sizeof(*material))))
		return (NULL);
	if (read_toml_type(toml, &value, "material", TOML_Table) == false)
		return (nfree(material));
	else if (!(material->material = read_material(value->value.table_v)))
		return (nfree(material));
	if (!(value = table_get(toml, "size")))
		material->size = 10;
	else if (read_digit(value, &material->size) == false)
		return (nfree(material));
	material->super.type = MATERIAL_MARBLE;
	return (material);
}
