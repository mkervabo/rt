#include "color.h"

uint32_t	color_to_rgb(t_color color)
{
	return (((uint32_t)color.r) << 16 | ((uint32_t)color.g) << 8 | color.b);
}

t_color		color_add(t_color a, t_color b)
{
	return ((t_color) {
		.r = (a.r + b.r) < a.r ? 255 : a.r + b.r,
		.g = (a.g + b.g) < a.g ? 255 : a.g + b.g,
		.b = (a.b + b.b) < a.b ? 255 : a.b + b.b
	});
}
