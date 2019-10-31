/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.sdl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:44:21 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/11/13 20:02:56 by mkervabo         ###   ########.fr       */
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

#define WINDOW_ERR "RT: Could not create SDL window: "

static bool	init_window(struct s_config *config, struct s_sdl_window *window)
{
	const char	*msg;

	SDL_Init(SDL_INIT_VIDEO);
	if (!(window->win = SDL_CreateWindow(config->name, SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, config->size.width,
					config->size.height, SDL_WINDOW_OPENGL))
			|| !(window->renderer = SDL_CreateRenderer(window->win, -1,
					SDL_RENDERER_ACCELERATED))
			|| !(window->screen = SDL_CreateTexture(window->renderer,
					SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
					config->size.width, config->size.height)))
	{
		write(STDERR_FILENO, WINDOW_ERR, sizeof(WINDOW_ERR) - 1);
		msg = SDL_GetError();
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
		return (false);
	}
	return (true);
}

static void	destroy_window(struct s_sdl_window *window)
{
	if (window->screen)
		SDL_DestroyTexture(window->screen);
	if (window->renderer)
		SDL_DestroyRenderer(window->renderer);
	if (window->win)
		SDL_DestroyWindow(window->win);
	SDL_Quit();
}

void		sdl_frontend(struct s_config *config)
{
	struct s_sdl_window	window;
	uint32_t			**pixels;
	size_t				nframes;
	size_t				i;

	window = (struct s_sdl_window) { .width = config->size.width };
	nframes = config->video ? config->video->frame : 1;
	if (!(pixels = malloc(sizeof(*pixels) * nframes)))
		return ;
	if (init_window(config, &window))
	{
		poll_events(&window, false);
		render_frames(config, &window, pixels, nframes);
		i = 0;
		while (i < config->scene.filters_size && !window.quit)
			apply_video_filter(config->scene.filters[i++], pixels,
			&nframes, config->size);
		render_video(config, &window, pixels, nframes);
	}
	i = 0;
	while (i < (config->video ? config->video->frame : 1))
		free(pixels[i++]);
	free(pixels);
	destroy_window(&window);
}

#define USAGE_PRE "Usage: "
#define USAGE_POST " [scene.toml]\n"

int			main(int argc, char *argv[])
{
	struct s_config	config;

	if (argc != 2)
	{
		write(STDERR_FILENO, USAGE_PRE, sizeof(USAGE_PRE) - 1);
		write(STDERR_FILENO, argv[0], ft_strlen(argv[0]));
		write(STDERR_FILENO, USAGE_POST, sizeof(USAGE_POST) - 1);
		return (1);
	}
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	if (read_config(argv[1], &config))
	{
		sdl_frontend(&config);
		free_config(&config);
		IMG_Quit();
		return (0);
	}
	IMG_Quit();
	return (1);
}
