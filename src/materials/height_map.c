#include "height_map.h"
#include "texture.h"
#include "config_utils.h"
#include "material_types.h"
#include "math/vec3.h"
#include <stdlib.h>
#include <SDL_image.h>

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
	
	printf("%f, %f\n", hit->u, hit->v);
	x = (hit->u > 0 ? hit->u : 1 - hit->u) / 2;
	y = (1 + hit->v) / 2;
	normal = vec3(hit->u, hit->v, (double)getpixel(material->surface, material->surface->w * x, material->surface->h * y) * ALTITUDE / 0xFFFFFF);
	p_u = vec3(hit->u + 1, hit->v, (double)getpixel(material->surface, fmod(material->surface->w * x + 1, material->surface->w), material->surface->h * y) * ALTITUDE / 0xFFFFFF);
	p_v = vec3(hit->u, hit->v + 1, (double)getpixel(material->surface, material->surface->w * x, fmod(material->surface->h * y + 1, material->surface->h)) * ALTITUDE / 0xFFFFFF);
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
		return (NULL);
	if (!(read_toml_type(toml, &value, "texture", TOML_String)))
		return (NULL);
	material->surface = IMG_Load(value->value.string_v);
	material->surface = SDL_ConvertSurfaceFormat(material->surface,
		SDL_PIXELFORMAT_ARGB8888, 0);
	if (read_toml_type(toml, &value, "material", TOML_Table) == false)
		return (nfree(material));
	else if (!(material->material = read_material(value->value.table_v)))
		return (nfree(material));
	material->super.type = MATERIAL_HEIGHT_MAP;
	return (material);
}
