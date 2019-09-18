#include "texture.h"
#include "material_types.h"
#include "config_utils.h"

#include <stdlib.h>
#include <SDL_image.h>

uint32_t					getpixel(SDL_Surface *surface, int x, int y)
{
	return (*(uint32_t *)(surface->pixels + y * surface->pitch + x * 4));
}

t_color						texture_color(struct s_texture *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	uint32_t	pixel;
	
	(void)scene;
	(void)ray;
	pixel = getpixel(material->surface, material->surface->w * hit->u, material->surface->h * hit->v);
	return ((t_color) {
		.r = (pixel >> 16) & 0xFF,
		.g = (pixel >> 8) & 0xFF,
		.b = (pixel) & 0xFF,
	});

}

struct s_texture	*read_texture(t_toml_table *toml)
{
	struct s_texture	*material;
	t_toml				*value;

	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate texture material"));
	if (!(read_toml_type(toml, &value, "texture", TOML_String)))
		return (rt_error(material, "Invalid texture in texture material"));
	if (!(material->surface = IMG_Load(value->value.string_v)))
		return (rt_error(material, IMG_GetError()));
	if (!(material->surface = SDL_ConvertSurfaceFormat(material->surface,
		SDL_PIXELFORMAT_ARGB8888, 0)))
		return (rt_error(material, "SDL_ConvertSurfaceFormat error in texture material"));
	material->super.type = MATERIAL_TEXTURE;
	return (material);
}
