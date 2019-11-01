#ifndef DEPTH_CONTRAST_FILTER_H
# define DEPTH_CONTRAST_FILTER_H

# include "filter.h"

struct s_depth_contrast_filter {
	t_filter	super;
};

void				depth_contrast_filter(struct s_depth_contrast_filter *filter, uint32_t *pixels, struct s_pixel_hit *hits, struct s_size window);
struct s_depth_contrast_filter	*read_depth_contrast_filter(t_toml_table *toml);

#endif
