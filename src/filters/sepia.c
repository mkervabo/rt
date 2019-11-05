#include "sepia.h"
#include "filter_types.h"
#include "config_utils.h"
#include "color.h"
#include "toml.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

void	sepia_filter(uint32_t *pixels, struct s_pixel_hit *hits, struct s_size window)
{
	size_t		i;
	t_color		color;
	uint16_t	r;
	uint16_t	g;
	uint16_t	b;

	(void)hits;
	i = 0;
	while (i < window.height * window.width)
	{
		color = color_from_rgb(pixels[i]);
		r = (color.r * 0.393) + (color.g * 0.769) + (color.b * 0.189);
		g = (color.r * 0.349) + (color.g * 0.686) + (color.b * 0.168);
		b = (color.r * 0.272) + (color.g * 0.534) + (color.b * 0.131);
		color.r = r > 255 ? 255 : r;
		color.g = g > 255 ? 255 : g;
		color.b = b > 255 ? 255 : b;
		pixels[i] = color_to_rgb(color);
		i++;
	}
}

struct s_sepia_filter	*read_sepia_filter(t_toml_table *toml)
{
	struct s_sepia_filter	*sepia;

	(void)toml;
	if (!(sepia = malloc(sizeof(*sepia))))
		return (rt_error(NULL, "Can not allocate sepia filter"));
	sepia->super.type = FILTER_SEPIA;
	return (sepia);
}

void						free_sepia_filter(struct s_sepia_filter *filter)
{
	free(filter);
}