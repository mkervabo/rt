#include "debug/assert.h"
#include "toml.h"
#include "config_utils.h"
#include "string_utils.h"

#include "material_types.h"
#include "normal_material.h"
#include "uv_material.h"
#include "move_uv_material.h"
#include "zoom_uv_material.h"
#include "color_material.h"
#include "reflection_material.h"
#include "texture.h"
#include "color_material.h"
#include "checkerboard_material.h"
#include "voronoi_material.h"
#include "diffuse_material.h"
#include "height_map.h"
#include "cartoon_material.h"
#include "perlin_material.h"
#include "marble_material.h"
#include "cloud_material.h"
#include "specular_material.h"
#include "random_material.h"
#include "xor_material.h"

#include <math.h>

static const struct s_material_record g_materials[] = {
	[MATERIAL_NORMAL] = { "NORMAL", (void *)normal_material_color, (void *)read_normal_material, (void*)normal_material_transparency },
	[MATERIAL_UV] = { "UV", (void *)uv_material_color, (void *)read_uv_material, (void*)uv_material_transparency },
	[MATERIAL_MOVE_UV] = { "MOVE_UV", (void *)move_uv_material_color, (void *)read_move_uv_material, (void*)move_uv_material_transparency },
	[MATERIAL_ZOOM_UV] = { "ZOOM_UV", (void *)zoom_uv_material_color, (void *)read_zoom_uv_material, (void*)zoom_uv_material_transparency },
	[MATERIAL_TEXTURE] = { "TEXTURE", (void *)texture_color, (void *)read_texture, (void*)texture_transparency },
	[MATERIAL_COLOR] = { "COLOR", (void *)color_material_color, (void *)read_color_material, (void*)color_material_transparency },
	[MATERIAL_CHECKERBOARD] = { "CHECKERBOARD", (void *)checkerboard_material_color, (void *)read_checkerboard_material, (void*)checkerboard_material_transparency },
	[MATERIAL_VORONOI] = { "VORONOI", (void *)voronoi_material_color, (void *)read_voronoi_material, (void*)voronoi_material_transparency },
	[MATERIAL_DIFFUSE] = { "DIFFUSE", (void *)diffuse_material_color, (void *)read_diffuse_material, (void*)diffuse_material_transparency },
	[MATERIAL_HEIGHT_MAP] = { "HEIGHT_MAP", (void *)height_map_color, (void *)read_height_map, (void*)height_map_transparency },
	[MATERIAL_CARTOON] = { "CARTOON", (void *)cartoon_material_color, (void *)read_cartoon_material, (void*)cartoon_material_transparency },
	[MATERIAL_REFLECTION] = { "REFLECTION", (void *)reflection_material_color, (void *)read_reflection_material, (void*)reflection_material_transparency },
	[MATERIAL_PERLIN] = { "PERLIN", (void *)perlin_material_color, (void *)read_perlin_material, (void*)perlin_material_transparency },
	[MATERIAL_MARBLE] = { "MARBLE", (void *)marble_material_color, (void *)read_marble_material, (void*)marble_material_transparency },
	[MATERIAL_CLOUD] = { "CLOUD", (void *)cloud_material_color, (void *)read_cloud_material, (void*)cloud_material_transparency },
	[MATERIAL_SPECULAR] = { "SPECULAR", (void *)specular_material_color, (void *)read_specular_material, (void*)specular_material_transparency },
	[MATERIAL_RANDOM] = { "RANDOM", (void *)random_material_color, (void *)read_random_material, (void*)random_material_transparency },
	[MATERIAL_XOR] = { "XOR", (void *)xor_material_color, (void *)read_xor_material, (void*)xor_material_transparency }
};

static double	clamp_uv(double uv)
{
	if (uv > 1 || uv < 0)
	{
		uv = fmod(uv, 1);
		return (uv < 0 ? 1 + uv : uv);
	}
	return (uv);
}

t_color		material_color(t_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	hit->u = clamp_uv(hit->u);
	hit->v = clamp_uv(hit->v);
	if (material->type <= (sizeof(g_materials) / sizeof(*g_materials)))
		return (g_materials[material->type].color(material, scene, ray, hit));
	else
	{
		assertf(false, "Unimplemented material type: %d", material->type);
		return ((t_color) { 0, 0, 0 });
	}
}


double		material_transparency(struct s_material *material, struct s_hit *hit, t_material **color)
{
	if (material->type <= (sizeof(g_materials) / sizeof(*g_materials)))
		return (g_materials[material->type].transparency(material, hit, color));
	else
		return (0.0);
}

t_material	*read_material(t_toml_table *toml)
{
	t_toml	*type;
	size_t	i;

	if (!(type = table_get(toml, "type")))
		return (NULL);
	if (type->type != TOML_String)
		return (NULL);
	i = 0;
	while (i < (sizeof(g_materials) / sizeof(*g_materials)))
	{
		if (ft_strcmp(type->value.string_v, g_materials[i].name) == 0)
			return (g_materials[i].read(toml));
		i++;
	}
	return (rt_error(NULL, "Invalid material type"));
}
