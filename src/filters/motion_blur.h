#ifndef FILTERS_MOTION_BLUR_H
# define FILTERS_MOTION_BLUR_H

# include "filter.h"

struct s_motion_blur_filter {
	t_filter	super;
};

void				motion_blur_video_filter(struct s_motion_blur_filter *filter, uint32_t **pixels, size_t *nframes, struct s_size window);
struct	s_motion_blur_filter	*read_motion_blur_filter(t_toml_table *toml);

#endif
