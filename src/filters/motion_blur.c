#include "motion_blur.h"
#include "filter_types.h"
#include "config_utils.h"
#include "color.h"

#include <stdlib.h>

static void			extract_and_add_rgb(uint32_t rgb, size_t *r, size_t *g, size_t *b)
{
	t_color	color;

	color = color_from_rgb(rgb);
	*r += color.r;
	*g += color.g;
	*b += color.b;
}

void				motion_blur_video_filter(struct s_motion_blur_filter *filter, uint32_t **pixels, size_t *nframes, struct s_size window)
{
	size_t	i;
	size_t	j;
	size_t	r;
	size_t	g;
	size_t	b;

	(void)filter;
	i = 0;
	while (i < window.width * window.height)
	{
		i++;
		j = 0;
		r = 0;
		g = 0;
		b = 0;
		while (j < *nframes)
			extract_and_add_rgb(pixels[j++][i], &r, &g, &b);
		pixels[0][i] = color_to_rgb((t_color) {
			.r = r / *nframes, .g = g / *nframes, .b = b / *nframes
		});
	}
	*nframes = 1;
}

struct s_motion_blur_filter	*read_motion_blur_filter(t_toml_table *toml)
{
	struct s_motion_blur_filter			*filter;

	(void)toml;
	if (!(filter = malloc(sizeof(*filter))))
		return (rt_error(NULL, "Can not allocate motion_blur filter"));
	filter->super.type = FILTER_MOTION_BLUR;
	return (filter);
}
