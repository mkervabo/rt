#include "texture.h"
#include "material_types.h"
#include "config_utils.h"

#include <stdlib.h>

t_color						texture_color(struct s_texture *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	uint32_t	pixel;

	(void)scene;
	(void)ray;
	pixel = getpixel(&material->image, material->image.size.width * hit->u, material->image.size.height * hit->v);
	return ((t_color) {
		.r = (pixel >> 16) & 0xFF,
		.g = (pixel >> 8) & 0xFF,
		.b = (pixel) & 0xFF,
	});

}

double	texture_transparency(struct s_texture *material, struct s_hit *hit)
{
	(void)material;
	(void)hit;
	return (0.0);
}

struct s_texture	*read_texture(t_toml_table *toml)
{
	struct s_texture	*material;
	t_toml				*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate texture material"));
	if (!(read_toml_type(toml, &value, "texture", TOML_String)))
		return (rt_error(material, "Invalid texture in texture material"));
	if (!load_image(&material->image, value->value.string_v))
		return (rt_error(material, get_image_error()));
	material->super.type = MATERIAL_TEXTURE;
	return (material);
}
