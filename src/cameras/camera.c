#include "camera.h"
#include "debug/assert.h"
#include "camera_types.h"
#include "perspective_camera.h"
#include "toml.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

struct s_ray	camera_create_ray(struct s_camera *camera, size_t x, size_t y,
			struct s_size window)
{
	struct s_ray	ray;

	if (camera->type == CAMERA_PERSPECTIVE)
		ray = perspective_camera_create_ray((struct s_perspective_camera *)camera, x, y, window);
	/*if (camera->type == MATERIAL_UV)
		return (uv_material_color((struct s_uv_material *)material, scene, ray, hit));
	if (camera->type == MATERIAL_TEXTURE)
		return (texture_color((struct s_texture *)material, scene, ray, hit));*/
	else
		assertf(false, "Unimplemented camera type: %d", camera->type);
	ray.origin = vec3_add(ray.origin, camera->position);
	ray.direction = vec3_rotate(ray.direction, camera->rotation);
	return (ray);
}

t_camera			*read_camera(t_toml_table *toml)
{
	t_toml	*type;

	if (!(type = table_get(toml, "type")))
		return (NULL);
	if (type->type != TOML_String)
		return (NULL);
	if (ft_strcmp(type->value.string_v, "PERSPECTIVE") == 0)
		return ((t_camera *)read_perspective_camera(toml));
	/*else if (ft_strcmp(type->value.string_v, "ORTHOGRAPHIC") == 0)
		return ((t_material *)read_uv_material(toml));
	else if (ft_strcmp(type->value.string_v, "360") == 0)
		return ((t_material *)read_texture(toml));*/
	else
		return (NULL);
}
