#include "math/size.h"
#include "color.h"
#include <stdint.h>
#include <stddef.h>
#include "filter_types.h"
#include "anti_aliasing.h"
#include "config_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "toml.h"

static t_color		merge_color_around(uint32_t *pixels, size_t i, struct s_size window)
{
	uint32_t	tmp[9];
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
	for (ssize_t y = -1; y <= 1; y++) {
		for (ssize_t x = -1; x <= 1; x++) {
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

void	anti_aliasing_filter(struct s_anti_aliasing_filter *aa, uint32_t *pixels, struct s_pixel_hit *hits, struct s_size window) {
	size_t			i;
	size_t			j;

	j = 0;
	while (j < aa->size)
	{
		i = 0;
		while (i < window.width * window.height)
		{
			if (i + window.width + 2 < window.width * window.height
			&& ((hits[i].t != hits[i + 2].t && hits[i].who != hits[i + 2].who)
			|| (hits[i].t != hits[i + window.width].t && hits[i].who != hits[i + window.width].who)
			|| (hits[i].t != hits[i + window.width + 2].t && hits[i].who != hits[i + window.width + 2].who)))
				{
					pixels[i] = color_to_rgb(merge_color_around(pixels, i, window));
				}
			i++;
		}
		j++;
	}
}

struct s_anti_aliasing_filter	*read_anti_aliasing_filter(t_toml_table *toml)
{
	struct s_anti_aliasing_filter	*anti_aliasing;
	t_toml							*value;

	if (!(anti_aliasing = malloc(sizeof(*anti_aliasing))))
		return (rt_error(NULL, "Can not allocate anti aliasing filter"));
	if (!(value = table_get(toml, "size")))
		anti_aliasing->size = 1;
	else if (read_digit(value, &anti_aliasing->size) == false)
		return (rt_error(anti_aliasing, "Invalid anti aliasing filter"));
	anti_aliasing->super.type = FILTER_ANTI_ALIASING;
	return (anti_aliasing);
}
