#include "color.h"

uint32_t	color_to_rgb(t_color color)
{
	return (((uint32_t)color.r) << 16 | ((uint32_t)color.g) << 8 | color.b);
}
