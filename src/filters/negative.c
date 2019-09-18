#include "math/size.h"
#include "color.h"
#include <stdint.h>
#include <stddef.h>
#include "filter_types.h"
#include "negative.h"
#include "config_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "toml.h"

void	negative_filter(uint32_t *pixels, struct s_pixel_hit *hits, struct s_size window)
{
	size_t	i;
	uint8_t	res;
	t_color	color;

	(void)hits;
	i = 0;
	while (i < window.height * window.width)
	{
		color = color_from_rgb(pixels[i]);
		res = ((uint16_t)color.r + (uint16_t)color.g + (uint16_t)color.b) / 3;
		color.r = 255 - color.r;
		color.g = 255 - color.g;
		color.b = 255 - color.b;
		pixels[i] = color_to_rgb(color);
		i++;
	}
}

struct s_negative_filter	*read_negative_filter(t_toml_table *toml)
{
	struct s_negative_filter	*negative;

	(void)toml;
	if (!(negative = malloc(sizeof(*negative))))
		return (NULL);
	negative->super.type = FILTER_NEGATIVE;
	return (negative);
}