#include "black_and_white.h"
#include "color.h"
#include "filter_types.h"
#include "config_utils.h"
#include <stdlib.h>

void	black_and_white_filter(uint32_t *pixels, struct s_pixel_hit *hits, struct s_size window)
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
		color.r = res;
		color.g = res;
		color.b = res;
		pixels[i] = color_to_rgb(color);
		i++;
	}
}

struct s_black_and_white_filter	*read_black_and_white_filter(t_toml_table *toml)
{
	struct s_black_and_white_filter	*black_and_white;

	(void)toml;
	if (!(black_and_white = malloc(sizeof(*black_and_white))))
		return (rt_error(NULL, "Can not allocate black and white filter"));
	black_and_white->super.type = FILTER_BLACK_AND_WHITE;
	return (black_and_white);
}
