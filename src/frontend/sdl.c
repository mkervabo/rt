/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:44:21 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/07/20 17:55:57 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frontend/sdl.h"
#include "render.h"
#include <SDL.h>
#include <stdbool.h>
#include <unistd.h>

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
}

static bool	update_render(uint32_t *pixels, void *user)
{
	struct s_sdl_window	*window;

	window = user;
	poll_events(window, false);
	SDL_UpdateTexture(window->screen, NULL, pixels,
					window->width * sizeof(uint32_t));
	SDL_RenderCopy(window->renderer, window->screen, NULL, NULL);
	SDL_RenderPresent(window->renderer);
	return (window->quit);
}

void	sdl_frontend(struct s_config *config)
{
	struct s_sdl_window	window;

	window = (struct s_sdl_window) { .width = config->size.width };
	if (init_window(config, &window))
	{
		render(&config->scene, config->size, update_render, &window);
		while (!window.quit)
			poll_events(&window, true);
	}
	destroy_window(&window);
}
