#include "debug/assert.h"
#include "toml.h"

#include "material_types.h"
#include "normal_material.h"
#include "uv_material.h"
#include "texture.h"
#include "color_material.h"
#include "checkerboard_material.h"
#include "voronoi_material.h"
#include "diffuse_material.h"
#include "height_map.h"
#include "cartoon_material.h"

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
	else if (material->type == MATERIAL_UV)
		return (uv_material_color((struct s_uv_material *)material, scene, ray, hit));
	else if (material->type == MATERIAL_TEXTURE)
		return (texture_color((struct s_texture *)material, scene, ray, hit));
	else if (material->type == MATERIAL_COLOR)
		return (color_material_color((struct s_color_material *)material, scene, ray, hit));
	else if (material->type == MATERIAL_CHECKERBOARD)
		return (checkerboard_material_color((struct s_checkerboard_material *)material, scene, ray, hit));
	else if (material->type == MATERIAL_VORONOI)
		return (voronoi_material_color((struct s_voronoi_material *)material, scene, ray, hit));
	else if (material->type == MATERIAL_DIFFUSE)
		return (diffuse_material_color((struct s_diffuse_material *)material, scene, ray, hit));
	else if (material->type == MATERIAL_HEIGHT_MAP)
		return (height_map_color((struct s_height_map *)material, scene, ray, hit));
	else if (material->type == MATERIAL_CARTOON)
		return (cartoon_material_color((struct s_cartoon_material *)material, scene, ray, hit));
	else
		assertf(false, "Unimplemented material type: %d", material->type);
}

t_material			*read_material(t_toml_table *toml)
{
	t_toml	*type;

	if (!(type = table_get(toml, "type")))
		return (NULL);
	if (type->type != TOML_String)
		return (NULL);
	if (ft_strcmp(type->value.string_v, "NORMAL") == 0)
		return ((t_material *)read_normal_material(toml));
	else if (ft_strcmp(type->value.string_v, "UV") == 0)
		return ((t_material *)read_uv_material(toml));
	else if (ft_strcmp(type->value.string_v, "TEXTURE") == 0)
		return ((t_material *)read_texture(toml));
	else if (ft_strcmp(type->value.string_v, "COLOR") == 0)
		return ((t_material *)read_color_material(toml));
	else if (ft_strcmp(type->value.string_v, "CHECKERBOARD") == 0)
		return ((t_material *)read_checkerboard_material(toml));	
	else if (ft_strcmp(type->value.string_v, "VORONOI") == 0)
		return ((t_material *)read_voronoi_material(toml));
	else if (ft_strcmp(type->value.string_v, "DIFFUSE") == 0)
		return ((t_material *)read_diffuse_material(toml));
	else if (ft_strcmp(type->value.string_v, "HEIGHT_MAP") == 0)
		return ((t_material *)read_height_map(toml));
	else if (ft_strcmp(type->value.string_v, "CARTOON") == 0)
		return ((t_material *)read_cartoon_material(toml));
	else
		return (NULL);
}
