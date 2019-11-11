/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.wasm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 09:20:28 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/11/14 09:29:25 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.wasm.h"

#include "config.h"
#include "object.h"
#include "filter.h"
#include "raytrace.h"
#include "string_utils.h"
#include <stdlib.h>

static bool			render_sub(t_scene *scene, struct s_size window,
	uint32_t *pixels, struct s_pixel_hit *hits)
{
	size_t				x;
	size_t				y;
	struct s_ray		ray;

	y = 0;
	while (y < window.height)
	{
		x = 0;
		while (x < window.width)
		{
			ray = camera_create_ray(scene->camera, x, window.height - y - 1,
				window);
			ray.n1 = 1.0;
			pixels[y * window.width + x] = color_to_rgb(raytrace(scene, ray,
				hits + y * window.width + x));
			x++;
		}
		if (rt_render_update(pixels, y * window.width))
			return (false);
		y++;
	}
	return (true);
}

static uint32_t		*render(t_scene *scene, struct s_size window)
{
	size_t				index;
	uint32_t			*pixels;
	struct s_pixel_hit	*hits;

	if (!(pixels = malloc(sizeof(*pixels) * window.width * window.height)))
		return (NULL);
	if (!(hits = malloc(sizeof(*hits) * window.width * window.height)))
		return (NULL);
	ft_memset(pixels, 0, sizeof(*pixels) * window.width * window.height);
	if (!render_sub(scene, window, pixels, hits))
		return (pixels);
	if (scene->filters)
	{
		index = 0;
		while (index < scene->filters_size)
			apply_filter(scene->filters[index++], pixels, hits, window);
	}
	rt_render_update(pixels, window.height * window.width);
	return (pixels);
}

uint32_t			*rt_render(char *file,
	size_t len) __attribute__((visibility("default")))
{
	struct s_config	config;
	t_reader		r;
	uint32_t		*pixels;

	r = create_reader(-1, file, len);
	r.len = len;
	if (read_config(&r, "config", &config))
	{
		pixels = render(&config.scene, config.size);
		free_config(&config);
		return (pixels);
	}
	return (NULL);
}
