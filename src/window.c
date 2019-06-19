/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:06:53 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/19 14:22:15 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <unistd.h>

void	*ft_memset(void *s, int c, size_t n)
{
	while (n--)
		((unsigned char *)s)[n] = c;
	return (s);
}

void	poll_events(t_win *window)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			window->quit = true;
		if (event.type == SDL_KEYDOWN
				&& event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			window->quit = true;
	}
}

bool	init_window(t_win *window)
{
	const char	*msg;

	SDL_Init(SDL_INIT_VIDEO);
	if (!(window->win = SDL_CreateWindow(window->name, SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, window->width, window->height,
					SDL_WINDOW_OPENGL))
			|| !(window->renderer = SDL_CreateRenderer(window->win, -1,
					SDL_RENDERER_ACCELERATED))
			|| !(window->screen = SDL_CreateTexture(window->renderer,
					SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
					window->width, window->height)))
	{
		free(window->name);
		write(STDERR_FILENO, WINDOW_ERR, sizeof(WINDOW_ERR) - 1);
		msg = SDL_GetError();
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
		return (false);
	}
	free(window->name);
	return (true);
}

void	destroy_window(t_win *window)
{
	if (window->screen)
		SDL_DestroyTexture(window->screen);
	if (window->renderer)
		SDL_DestroyRenderer(window->renderer);
	if (window->win)
		SDL_DestroyWindow(window->win);
	SDL_Quit();
}
