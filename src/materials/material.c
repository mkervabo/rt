#include "material.h"
#include "debug/assert.h"
#include "material_types.h"
#include "normal_material.h"
#include "uv_material.h"
#include "texture.h"
#include "toml.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

t_color			material_color(t_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	if (material->type == MATERIAL_NORMAL)
		return (normal_material_color((struct s_normal_material *)material, scene, ray, hit));
	if (material->type == MATERIAL_UV)
		return (uv_material_color((struct s_uv_material *)material, scene, ray, hit));
	if (material->type == MATERIAL_TEXTURE)
		return (texture_color((struct s_texture *)material, scene, ray, hit));
	else
		assertf(false, "Unimplemented material type: %d", material->type);
}

t_material			*read_material(t_toml_table *toml)
{
	t_toml	*type;

	if (!(type = table_get(toml, "material")))
		return (NULL);
	if (type->type != TOML_String)
		return (NULL);
	if (ft_strcmp(type->value.string_v, "NORMAL") == 0)
		return ((t_material *)read_normal_material(toml));
	else if (ft_strcmp(type->value.string_v, "UV") == 0)
		return ((t_material *)read_uv_material(toml));
	else if (ft_strcmp(type->value.string_v, "TEXTURE") == 0)
		return ((t_material *)read_texture(toml));
	else
		return (NULL);
}
