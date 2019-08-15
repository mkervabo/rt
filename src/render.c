/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:40:18 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/09/12 19:47:36 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "object.h"
#include "filter.h"
#include "raytrace.h"
#include <stdlib.h>

static void		*ft_memset(void *s, int c, size_t n)
{
	while (n--)
		((unsigned char *)s)[n] = c;
	return (s);
}

uint32_t		*render(t_scene *scene, struct s_size window, t_update_fn update, void *user)
{
	size_t				x;
	size_t				y;
	size_t				index;
	struct s_ray		ray;
	uint32_t			*pixels;
	struct s_pixel_hit	*hits;

	if (!(pixels = malloc(sizeof(*pixels) * window.width * window.height)))
		return (NULL);
	if (!(hits = malloc(sizeof(*hits) * window.width * window.height)))
		return (NULL);
	ft_memset(pixels, 0, sizeof(*pixels) * window.width * window.height);
	y = -1;
	while (++y < window.height)
	{
		x = 0;
		while (x < window.width)
		{
			ray = camera_create_ray(scene->camera, x, window.height - y - 1, window);
			ray.n1 = 1.0;
			pixels[y * window.width + x] = color_to_rgb(raytrace(scene, ray, hits +  y * window.width + x));
			x++;
		}
		if (update(pixels, user))
			return (pixels);
	}
	if (scene->filters)
	{
		index = 0;
		while (index < scene->filters_size)
			apply_filter(scene->filters[index++], pixels, hits, window);
	}
	update(pixels, user);
	return (pixels);
}
