/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:44:21 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/10/30 19:55:55 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frontend/sdl.h"
#include "render.h"
#include "video.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>

# define WINDOW_ERR "RT: Could not create SDL window: "

struct s_sdl_window {
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Texture		*screen;
	size_t			width;
	bool			quit;
};

static size_t	ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	while (str[size])
		size++;
	return (size);
}

static bool	init_window(struct s_config *config, struct s_sdl_window *window)
{
	const char	*msg;

	SDL_Init(SDL_INIT_VIDEO);
	if (!(window->win = SDL_CreateWindow(config->name, SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, config->size.width, config->size.height,
					SDL_WINDOW_OPENGL))
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

/**
** If wait is true we use WaitEvent instead of PollEvent to avoid using 100% cpu while
** iddle
**/
static void	poll_events(struct s_sdl_window *window, bool wait)
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
			break;
	}
	SDL_RenderCopy(window->renderer, window->screen, NULL, NULL);
	SDL_RenderPresent(window->renderer);
}

static bool	update_render(uint32_t *pixels, void *user)
{
	struct s_sdl_window	*window;

	window = user;
	SDL_UpdateTexture(window->screen, NULL, pixels,
					window->width * sizeof(uint32_t));
	poll_events(window, false);
	return (window->quit);
}

void	sdl_frontend(struct s_config *config)
{
	struct s_sdl_window	window;
	uint32_t	**pixels;
	size_t		i;
	char		name[25];

	window = (struct s_sdl_window) { .width = config->size.width };
	if (!(pixels = malloc(sizeof(*pixels) * (config->video ? config->video->frame : 1))))
		return ;
	i = 0;
	if (init_window(config, &window))
	{
		while (i < (config->video ? config->video->frame : 1) && !window.quit)
		{
			video_transform_scene(config, i);
			pixels[i] = render(&config->scene, config->size, update_render, &window);
			mkdir("./video", 0700);
			snprintf(name, sizeof name, "./video/frame_%05zu.png", i + 1);
			IMG_SavePNG(SDL_CreateRGBSurfaceFrom(pixels[i], config->size.width, config->size.height, 32, 4 * config->size.width, 0xff0000, 0xff00, 0xff, 0), name);
			i++;
		}
		while (!window.quit)
		{
			i = 0;
			while (i < (config->video ? config->video->frame : 1) && !window.quit)
			{
				SDL_UpdateTexture(window.screen, NULL, pixels[i],
					window.width * sizeof(uint32_t));
				poll_events(&window, false);
				if (config->video)
					SDL_Delay(1000 / config->video->frame_sec);
				i++;
			}
		}
	}
	destroy_window(&window);
}
