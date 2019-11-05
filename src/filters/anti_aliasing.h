#ifndef ANTI_ALIASING_FILTER_H
# define ANTI_ALIASING_FILTER_H

# include "filter.h"

struct s_anti_aliasing_filter {
	t_filter	super;
	double		size;
};

void		anti_aliasing_filter(struct s_anti_aliasing_filter *aa, uint32_t *pixels, struct s_pixel_hit *hits, struct s_size window);
struct s_anti_aliasing_filter	*read_anti_aliasing_filter(t_toml_table *toml);
void							free_anti_aliasing_filter(struct s_anti_aliasing_filter *filter);
#endif
