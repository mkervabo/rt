#include "math/size.h"
#include "color.h"
#include <stdint.h>
#include <stddef.h>
#include "filter_types.h"
#include "blur.h"
#include "config_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "toml.h"

static t_color		merge_color_around(uint32_t *pixels, size_t i, struct s_size window)
{
	uint32_t	tmp[25];
	ssize_t		p;
	size_t		j;
	t_color		color;
	uint16_t	r;
	uint16_t	g;
	uint16_t	b;

	r = 0;
	g = 0;
	b = 0;
	j = 0;
	for (ssize_t y = -2; y <= 2; y++) {
		for (ssize_t x = -2; x <= 2; x++) {
			p = (ssize_t)i + y * window.width + x;
			if (p >= 0 && p < window.width * window.height)
				tmp[j++] = pixels[(size_t)p];
		}
	}
	i = 0;
	while (i < j)
	{
		color = color_from_rgb(tmp[i]);
		r += color.r;
		g += color.g;
		b += color.b;
		i++;
	}
	return ((t_color) {
		.r = r / j,
		.g = g / j,
		.b = b / j
	});
}

void	blur_filter(struct s_blur_filter *blur, uint32_t *pixels, struct s_pixel_hit *hits, struct s_size window) {
	size_t			i;
	size_t			j;

	(void)hits;
	j = 0;
	while (j < blur->size)
	{
		i = 0;
		while (i < window.width * window.height)
		{
			pixels[i] = color_to_rgb(merge_color_around(pixels, i, window));
			i++;
		}
		j++;
	}
}

struct s_blur_filter	*read_blur_filter(t_toml_table *toml)
{
	struct s_blur_filter	*blur;
	t_toml			*value;

	if (!(blur = malloc(sizeof(*blur))))
		return (rt_error(NULL, "Can not allocate blur filter"));
	if (!(value = table_get(toml, "size")))
		blur->size = 1;
	else if (!read_digit(value, &blur->size))
		return (rt_error(blur, "Invalid blur filter"));
	blur->super.type = FILTER_BLUR;
	return (blur);
}
