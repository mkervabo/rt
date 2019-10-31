/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 20:00:03 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/13 20:00:34 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.sdl.h"

#include "render.h"
#include "video.h"
#include "config.h"
#include "image.h"
#include "filter.h"
#include "string_utils.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stddef.h>

void	poll_events(struct s_sdl_window *window, bool wait)
{
	SDL_Event	event;

	while (wait || SDL_PollEvent(&event))
	{
		if (wait)
			SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			window->quit = true;
		if (event.type == SDL_KEYDOWN
				&& event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			window->quit = true;
		if (wait)
			break ;
	}
	SDL_RenderCopy(window->renderer, window->screen, NULL, NULL);
	SDL_RenderPresent(window->renderer);
}

bool	update_render(uint32_t *pixels, void *user)
{
	struct s_sdl_window	*window;

	window = user;
	SDL_UpdateTexture(window->screen, NULL, pixels,
					window->width * sizeof(uint32_t));
	poll_events(window, false);
	return (window->quit);
}

void	render_frames(struct s_config *config, struct s_sdl_window *window,
	uint32_t **pixels, size_t nframes)
{
	size_t		i;
	char		name[25];
	SDL_Surface *image;

	i = 0;
	while (i < nframes && !window->quit)
	{
		video_transform_scene(config, i);
		pixels[i] = render(&config->scene, config->size, update_render, window);
		mkdir("./video", 0700);
		snprintf(name, sizeof(name), "./video/frame_%05zu.png", i + 1);
		image = SDL_CreateRGBSurfaceFrom(pixels[i],
			config->size.width, config->size.height, 32, 4 * config->size.width,
			0xff0000, 0xff00, 0xff, 0);
		IMG_SavePNG(image, name);
		SDL_FreeSurface(image);
		i++;
	}
}

void	render_video(struct s_config *config, struct s_sdl_window *window,
	uint32_t **pixels, size_t nframes)
{
	size_t i;

	i = 0;
	while (!window->quit)
	{
		i = 0;
		while (i < nframes && !window->quit)
		{
			SDL_UpdateTexture(window->screen, NULL, pixels[i],
				window->width * sizeof(uint32_t));
			poll_events(window, false);
			if (config->video)
				SDL_Delay(1000 / config->video->frame_sec);
			i++;
		}
	}
}
