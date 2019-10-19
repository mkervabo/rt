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

void					cartoon_filter(uint32_t *pixels, struct s_pixel_hit *hits, struct s_size window) {
	size_t			i;

	i = 0;
	while (i < window.width * window.height)
	{
		if (i + window.width + 2 < window.width * window.height
		&& ((hits[i].t != hits[i + 2].t && hits[i].who != hits[i + 2].who)
		|| (hits[i].t != hits[i + window.width].t && hits[i].who != hits[i + window.width].who)
		|| (hits[i].t != hits[i + window.width + 2].t && hits[i].who != hits[i + window.width + 2].who)))
			{
				pixels[i] = color_to_rgb((t_color){ .r = 0, .g = 0, .b = 0 });
			}
		i++;
	}
}

struct s_cartoon_filter	*read_cartoon_filter(t_toml_table *toml)
{
	struct s_cartoon_filter	*cartoon;
	t_toml							*value;

	if (!(cartoon = malloc(sizeof(*cartoon))))
		return (rt_error(NULL, "Can not allocate cartoon filter"));
	cartoon->super.type = FILTER_CARTOON;
	return (cartoon);
}
