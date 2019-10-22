#ifndef CARTOON_FILTER_H
# define CARTOON_FILTER_H

# include "filter.h"

struct s_cartoon_filter {
	t_filter	super;
	t_color		color;
};

void		cartoon_filter(struct s_cartoon_filter *filter, uint32_t *pixels, struct s_pixel_hit *hits, struct s_size window);
struct		s_cartoon_filter	*read_cartoon_filter(t_toml_table *toml);

#endif
