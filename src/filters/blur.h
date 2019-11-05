#ifndef BLUR_FILTER_H
# define BLUR_FILTER_H

# include "filter.h"

struct s_blur_filter {
	t_filter	super;
	double		size;
};

void					blur_filter(struct s_blur_filter *blur, uint32_t *pixels, struct s_pixel_hit *hits, struct s_size window);
struct s_blur_filter	*read_blur_filter(t_toml_table *toml);
void					free_blur_filter(struct s_blur_filter *filter);

#endif
