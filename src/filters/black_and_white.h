#ifndef BLACK_AND_WHITE_FILTER_H
# define BLACK_AND_WHITE_FILTER_H

# include "filter.h"

struct s_black_and_white_filter {
	t_filter	super;
};

void					black_and_white_filter(uint32_t *pixels, struct s_pixel_hit *hits, struct s_size window);
struct s_black_and_white_filter	*read_black_and_white_filter(t_toml_table *toml);

#endif
