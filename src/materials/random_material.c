#include "random_material.h"
#include "material_types.h"
#include "config_utils.h"

#include <stdlib.h>

t_color						random_material_color(struct s_random_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	(void)material;
	(void)scene;
	(void)ray;
	(void)hit;

	return ((t_color) {
		.r = rand(),
		.g = rand(),
		.b = rand()
	});

}

double	random_material_transparency(struct s_random_material *material, struct s_hit *hit)
{
	(void)material;
	(void)hit;
	return (0.0);
}

struct s_random_material	*read_random_material(t_toml_table *toml)
{
	struct s_random_material	*material;

	(void)toml;
	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate random material"));
	material->super.type = MATERIAL_RANDOM;
	return (material);
}

void						free_random_material(struct s_random_material *material)
{
	free(material);
}
