/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:05:12 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/12 15:28:22 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <stdbool.h>
# include <stddef.h>

# include "math/size.h"

# include <stdbool.h>
# include <stddef.h>

typedef struct	s_image
{
	struct s_size	size;
	uint32_t		*pixels;
	void			*cookie;
}				t_image;

bool			load_image(t_image *dst, const char *path);
const char		*get_image_error(void);
uint32_t		getpixel(t_image *image, size_t x, size_t y);
void			free_image(t_image *image);

#endif
