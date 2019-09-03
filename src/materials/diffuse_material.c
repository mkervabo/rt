#include "diffuse_material.h"
#include "raytrace.h"
#include "material_types.h"
#include "config_utils.h"

#include <stdlib.h>
#include <math.h>

static t_color color_mult_vec3(t_color color, t_vec3 vec) {
	return ((t_color) {
		.r = color.r * vec.x,
		.g = color.g * vec.y,
		.b = color.b * vec.z
	});
}

static bool	receive_light(t_scene *scene, struct s_light_ray *light, t_vec3 p) {
	struct s_ray	shadow;
	t_vec3			to_light;
	t_vec3			direction;
	double			dist;
	struct s_hit	hit;

	to_light = vec3_sub(light->origin, p);
	dist = vec3_length(to_light);
	direction = vec3_divv(to_light, dist);
	shadow = (struct s_ray) {
		.origin = p,
		.direction = direction
	};
	hit = hit_scene(scene, shadow);
	if (hit.t >= 0 && hit.t <= dist)
		return (false);
	else
		return (true);
}

# define SHADOW_BIAS 1e-4

t_color		diffuse_material_color(struct s_diffuse_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	size_t				i;
	struct s_light_ray	light;
	t_color				light_color; // r g b as x y z
	double				intensity;
	t_vec3				point;

	light_color = (t_color){ 0, 0, 0 };
	point = vec3_add(ray_point_at(&ray, hit->t), vec3_multv(hit->normal, SHADOW_BIAS));
	i = 0;
	while (i < scene->lights_size) {
		light = get_light_ray(scene->lights[i], ray_point_at(&ray, hit->t));
		if (vec3_is_zero(light.direction))
			intensity = light.intensity;
		else if (receive_light(scene, &light, point))
			intensity = material->albedo / M_PI * fmax(vec3_dot(vec3_multv(light.direction, -1), hit->normal), 0) * light.intensity;
		else
			intensity = 0;
		light_color = color_add(light_color, color_multv(
			light.color,
			intensity
		));
		i++;
	}
	return (color_ratio(
		material_color(material->material, scene, ray, hit),
		light_color
	));
}

struct s_diffuse_material	*read_diffuse_material(t_toml_table *toml)
{
	struct s_diffuse_material	*material;
	t_toml					*value;

	if (!(material = malloc(sizeof(*material))))
		return (NULL);
	if (!(value = table_get(toml, "albedo")))
		return (nfree(material));
	if (!read_digit(value, &material->albedo))
		return (nfree(material));
	if (!read_toml_type(toml, &value, "material", TOML_Table))
		return (nfree(material));
	if (!(material->material = read_material(value->value.table_v)))
		return (nfree(material));
	material->super.type = MATERIAL_DIFFUSE;
	return (material);
}
