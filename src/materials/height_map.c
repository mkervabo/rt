#include "height_map.h"
#include "config_utils.h"
#include "material_types.h"
#include "math/vec3.h"

#include <stdlib.h>
#include <math.h>

#define ALTITUDE 200 //atiltude du blanc

static t_vec3	 new_normal(t_vec3 p1, t_vec3 p2 , t_vec3 p3)
{
	t_vec3 AB;
	t_vec3 AC;
	t_vec3 norm;

	AB = vec3_sub(p2, p1);
	AC = vec3_sub(p3, p1);
	norm = vec3_cross(AB, AC);
	norm.y *= -1;
	norm = vec3_unit(norm);
	return norm;
}

t_color						height_map_color(struct s_height_map *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	t_vec3		normal;
	t_vec3		p_u;
	t_vec3		p_v;
	double		x;
	double		y;
	
	x = (hit->u > 0 ? hit->u : 1 - hit->u) / 2;
	y = (1 + hit->v) / 2;
	normal = vec3(hit->u, hit->v, (double)getpixel(&material->image, material->image.size.width * x, material->image.size.height * y) * ALTITUDE / 0xFFFFFF);
	p_u = vec3(hit->u + 1, hit->v, (double)getpixel(&material->image, fmod(material->image.size.width * x + 1, material->image.size.width), material->image.size.height * y) * ALTITUDE / 0xFFFFFF);
	p_v = vec3(hit->u, hit->v + 1, (double)getpixel(&material->image, material->image.size.width * x, fmod(material->image.size.height * y + 1, material->image.size.height)) * ALTITUDE / 0xFFFFFF);
	normal = new_normal(normal, p_u, p_v);
	normal = vec3_unit(vec3_add(hit->normal, normal));
	hit->normal = normal;
	return (material_color(material->material, scene, ray, hit));
}


struct s_height_map	*read_height_map(t_toml_table *toml)
{
	struct s_height_map	*material;
	t_toml					*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate height map material"));
	if (!(read_toml_type(toml, &value, "texture", TOML_String)))
		return (rt_error(material, "Missing texture in height map material"));
	if (!load_image(&material->image, value->value.string_v))
		return (rt_error(material, get_image_error()));
	if (read_toml_type(toml, &value, "material", TOML_Table) == false)
		return (rt_error(material, "Misssing material in height map material"));
	if (!(material->material = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid material in height map material"));
	material->super.type = MATERIAL_HEIGHT_MAP;
	return (material);
}
