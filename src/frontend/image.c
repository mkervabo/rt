/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:02:05 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:25:16 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

bool		load_image(t_image *dst, const char *path)
{
	SDL_Surface *surface;
	SDL_Surface *converted;

	if (!(surface = IMG_Load(path)))
		return (false);
	if (!(converted = SDL_ConvertSurfaceFormat(surface,
		SDL_PIXELFORMAT_ARGB8888, 0)))
	{
		SDL_FreeSurface(surface);
		return (false);
	}
	SDL_FreeSurface(surface);
	*dst = (t_image) {
		.size.width = converted->w,
		.size.height = converted->h,
		.pixels = converted->pixels,
		.cookie = converted
	};
	return (true);
}

const char	*get_image_error(void)
{
	return (IMG_GetError());
}

uint32_t	getpixel(t_image *image, size_t x, size_t y)
{
	return (image->pixels[y * image->size.width + x]);
}

void		free_image(t_image *image)
{
	SDL_FreeSurface((SDL_Surface *)image->cookie);
}
