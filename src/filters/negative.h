#ifndef NEGATIVE_FILTER_H
# define NEGATIVE_FILTER_H

# include "filter.h"

struct s_negative_filter {
	t_filter	super;
};

void					negative_filter(uint32_t *pixels, struct s_pixel_hit *hits, struct s_size window);
struct s_negative_filter	*read_negative_filter(t_toml_table *toml);
void						free_negative_filter(struct s_negative_filter *filter);
#endif
