#include "reflection_material.h"
#include "config_utils.h"
#include "material_types.h"
#include "raytrace.h"
#include "math/utils.h"
#include <math.h>
#include <stdlib.h>
#define MAX_DEPTH 5

static void		move_origin(struct s_ray *ray, t_vec3 tmp, t_vec3 nm)
{
	double dot;

	dot = vec3_dot(tmp, nm);
	nm = vec3_multv(nm, 1e-6);
	if (dot < 0)
		ray->origin = vec3_sub(ray->origin, nm);
	else
		ray->origin = vec3_add(ray->origin, nm);
}

double		reflection_material_transparency(struct s_reflection_material *material, struct s_hit *hit, t_material **color)
{
	double	value;
	double	value_mat;

	*color = material->color;
	value = material->transparency / 100;
	if ((value_mat = material_transparency(material->color, hit, color)) != 0)
		value *= value_mat;
	return (value);
}

t_color		reflection(t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	ray.origin = ray_point_at(&ray, hit->t - 0.01);
	ray.direction = vec3_unit(vec3_sub(
		ray.direction,
		vec3_multv(hit->normal, 2 * vec3_dot(hit->normal, ray.direction))
	));
	return (raytrace(scene, ray, NULL));
}

t_color		refraction(t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	double			n;
	double			cos_t;
	double			sin_t;
	t_vec3			tmp;

	ray.origin = ray_point_at(&ray, hit->t);
	tmp = ray.direction;
	cos_t = clamp(vec3_dot(ray.direction, hit->normal), -1.0, 1.0);

	if (cos_t < 0)
		cos_t *= -1.0;
	else
	{
		dswap(&ray.n1, &ray.n2);
		hit->normal = vec3_multv(hit->normal, -1.0);
	}
	n = ray.n1 / ray.n2;
	sin_t = 1.0 - n * n * (1.0 - cos_t * cos_t);
	if (sin_t > 0)
	{
		ray.direction.x = (ray.direction.x + cos_t * hit->normal.x) * n - hit->normal.x * sqrt(sin_t);
		ray.direction.y = (ray.direction.y + cos_t * hit->normal.y) * n - hit->normal.y * sqrt(sin_t);
		ray.direction.z = (ray.direction.z + cos_t * hit->normal.z) * n - hit->normal.z * sqrt(sin_t);
		ray.direction = vec3_unit(ray.direction);
	}
	else
		return (reflection(scene, ray, hit));
	move_origin(&ray, tmp, hit->normal);
	return (raytrace(scene, ray, NULL));
}

t_color		reflection_material_color(struct s_reflection_material *material,
									t_scene *scene,
									struct s_ray ray,
									struct s_hit *hit)
{
	t_color color;
	t_color reflect_color;
	t_color refract_color;

	ray.n2 = material->refraction;

	refract_color = (t_color) { 0, 0, 0 };
	reflect_color = (t_color) { 0, 0, 0 };

	ray.depth++;
	color = material_color(material->color, scene, ray, hit);
	if (material->reflection + material->transparency > 100)
		scale(&material->reflection, &material->transparency, 100);
	color = color_multv(color, (100 - material->transparency - material->reflection) / 100.0);
	if (material->reflection > 0 && ray.depth < MAX_DEPTH)
		reflect_color = reflection(scene, ray, hit);
	if (material->refraction >= 1.0 && material->transparency > 0 && ray.depth < MAX_DEPTH)
		refract_color = refraction(scene, ray, hit);
	reflect_color = color_multv(reflect_color, material->reflection / 100);
	refract_color = color_multv(refract_color, material->transparency / 100);
	color = color_add(color, color_add(reflect_color, refract_color));
	return (color);
}

struct s_reflection_material	*read_reflection_material(t_toml_table *toml)
{
	struct s_reflection_material	*material;
	t_toml							*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate reflection material"));
	if (!(value = table_get(toml, "reflection")))
		material->reflection = 0;
	else if (!read_digit(value, &material->reflection))
		return (rt_error(material, "Invalid reflection in reflection material"));
	if (!(value = table_get(toml, "transparency")))
		material->transparency = 0;
	else if (!read_digit(value, &material->transparency))
		return (rt_error(material, "Invalid transparency in reflection material"));
	if (!(value = table_get(toml, "refraction")))
		material->refraction = 1;
	else if (!read_digit(value, &material->refraction))
		return (rt_error(material, "Invalid refraction in reflection material"));
	if (read_toml_type(toml, &value, "color", TOML_Table) == false)
		return (rt_error(material, "Mising color in reflection material"));
	else if (!(material->color = read_material(value->value.table_v)))
		return (rt_error(material, "Invalid color in reflection material"));
	material->super.type = MATERIAL_REFLECTION;
	return (material);
}

void					free_reflection_material(struct s_reflection_material *material)
{
	free(material->color);
	free(material);
}
