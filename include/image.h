#ifndef IMAGE_H
# define IMAGE_H

# include "math/size.h"

typedef struct	s_image {
	struct s_size	size;
	uint32_t		*pixels;
	void			*cookie;
}				t_image;

bool		load_image(t_image *dst, const char *path);
const char	*get_image_error(void);
uint32_t	getpixel(t_image *image, size_t x, size_t y);
void		free_image(t_image *image);

#endif
