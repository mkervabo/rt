#ifndef SEPIA_FILTER_H
# define SEPIA_FILTER_H

# include "filter.h"

struct s_sepia_filter {
	t_filter	super;
};

void					sepia_filter(uint32_t *pixels, struct s_pixel_hit *hits, struct s_size window);
struct s_sepia_filter	*read_sepia_filter(t_toml_table *toml);

#endif
