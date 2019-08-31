/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:40:18 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/08/31 14:56:19 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "raytrace.h"

#include <stdlib.h>

static void    *ft_memset(void *s, int c, size_t n)
{
	while (n--)
		((unsigned char *)s)[n] = c;
	return (s);
}

uint32_t	*render(t_scene *scene, struct s_size window, t_update_fn update, void *user)
{
	size_t			x;
	size_t			y;
	struct s_ray	ray;
	uint32_t		*pixels;

	if (!(pixels = malloc(sizeof(uint32_t) * window.width * window.height)))
		return (NULL);
	ft_memset(pixels, 0, sizeof(uint32_t) * window.width * window.height);
	y = -1;
	while (++y < window.height)
	{
		x = 0;
		while (x < window.width)
		{
			ray = camera_create_ray(scene->camera, x, window.height - y - 1, window);
			pixels[y * window.width + x] = color_to_rgb(raytrace(scene, ray));
			x++;
		}
		if (update(pixels, user))
			break ;
	}
	return (pixels);
}
