#include "math/size.h"
#include "color.h"
#include <stdint.h>
#include <stddef.h>
#include "filter_types.h"
#include "cartoon.h"
#include "config_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "toml.h"

static bool	read_color(t_toml_table *toml, t_color *color)
{
	t_toml	*value;

	if (!(value = table_get(toml, "r")))
		color->r = 0;
	else if (value->type != TOML_Integer)
		return ((bool)rt_error(NULL, "Is not a interger in red color"));
	else
		color->r = value->value.integer_v;
	if (!(value = table_get(toml, "g")))
		color->g = 0;
	else if (value->type != TOML_Integer)
		return ((bool)rt_error(NULL, "Is not a interger in green color"));
	else
		color->g = value->value.integer_v;
	if (!(value = table_get(toml, "b")))
		color->b = 0;
	else if (value->type != TOML_Integer)
		return ((bool)rt_error(NULL, "Is not a interger in blue color"));
	else
		color->b = value->value.integer_v;
	return (true);
}

void					cartoon_filter(struct s_cartoon_filter *filter,
										uint32_t *pixels,
										struct s_pixel_hit *hits,
										struct s_size window) {
	size_t			i;
	t_color			color;

	i = 0;
	while (i < window.width * window.height)
	{
		if (i + window.width + 2 < window.width * window.height
		&& ((hits[i].t != hits[i + 2].t && hits[i].who != hits[i + 2].who)
		|| (hits[i].t != hits[i + window.width].t && hits[i].who != hits[i + window.width].who)
		|| (hits[i].t != hits[i + window.width + 2].t && hits[i].who != hits[i + window.width + 2].who)))
			{
				pixels[i] = color_to_rgb(filter->color);
			}
		i++;
	}
}

struct s_cartoon_filter	*read_cartoon_filter(t_toml_table *toml)
{
	struct s_cartoon_filter			*filter;
	t_toml							*value;

	if (!(filter = malloc(sizeof(*filter))))
		return (rt_error(NULL, "Can not allocate cartoon filter"));
	if (read_toml_type(toml, &value, "color", TOML_Table) == false)
		filter->color = (t_color) { 0, 0, 0 };
	else if (!read_color(value->value.table_v, &filter->color))
		return (rt_error(filter, "Invalid color filter"));
	filter->super.type = FILTER_CARTOON;
	return (filter);
}
