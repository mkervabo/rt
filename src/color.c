#include "color.h"
#include "debug/assert.h"

uint32_t	color_to_rgb(t_color color)
{
	return (((uint32_t)color.r) << 16 | ((uint32_t)color.g) << 8 | color.b);
}

t_color color_from_rgb(uint32_t color)
{
	return ((t_color) {
		.r = (color >> 16) & 0xFF,
		.g = (color >> 8) & 0xFF,
		.b = color & 0xFF
	});
}


t_color		color_add(t_color a, t_color b)
{
	t_color res = ((t_color) {
		.r = (uint8_t)(a.r + b.r) < a.r ? 255 : (a.r + b.r),
		.g = (uint8_t)(a.g + b.g) < a.g ? 255 : (a.g + b.g),
		.b = (uint8_t)(a.b + b.b) < a.b ? 255 : (a.b + b.b)
	});
	return (res);
}

static uint8_t clamp(double v) {
	if (v < 0)
		return (0);
	else if (v > 255)
		return (255);
	else
		return (v);
}

t_color		color_multv(t_color c, double v)
{
	assertf(v >= 0 && v <= 1, "color_multv: v must be between 0 and 1 but got %f", v);

	return ((t_color) {
		.r = clamp((double)c.r * v),
		.g = clamp((double)c.g * v),
		.b = clamp((double)c.b * v)
	});
}

t_color		color_ratio(t_color a, t_color b)
{
	return ((t_color) {
		.r = ((uint16_t)a.r * (uint16_t)b.r) / 255,
		.g = ((uint16_t)a.g * (uint16_t)b.g) / 255,
		.b = ((uint16_t)a.b * (uint16_t)b.b) / 255,
	});
}
