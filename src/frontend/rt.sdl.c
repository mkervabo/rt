/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:44:21 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/11/09 21:06:26 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderers/pthread.h"
#include "video.h"
#include "config.h"
#include "image.h"
#include "filter.h"

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

void	sdl_frontend(struct s_config *config, t_pthread_renderer *renderer)
{
	struct s_sdl_window	window;
	uint32_t	**pixels;
	size_t		i;
	char		name[25];
	size_t		nframes;

	window = (struct s_sdl_window) { .width = config->size.width };
	nframes = config->video ? config->video->frame : 1;
	if (!(pixels = malloc(sizeof(*pixels) * nframes)))
		return ;
	i = 0;
	if (init_window(config, &window))
	{
		poll_events(&window, false);
		while (i < nframes && !window.quit)
		{
			video_transform_scene(config, i);
			pixels[i] = pthread_render(renderer, update_render, &window);
			mkdir("./video", 0700);
			snprintf(name, sizeof name, "./video/frame_%05zu.png", i + 1);
			IMG_SavePNG(SDL_CreateRGBSurfaceFrom(pixels[i], config->size.width, config->size.height, 32, 4 * config->size.width, 0xff0000, 0xff00, 0xff, 0), name);
			i++;
		}
		i = 0;
		while (i < config->scene.filters_size && !window.quit)
			apply_video_filter(config->scene.filters[i++], pixels, &nframes, config->size);
		while (!window.quit)
		{
			i = 0;
			while (i < nframes && !window.quit)
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

#define USAGE_PRE "Usage: "
#define USAGE_POST " [scene.toml]\n"

int	main(int argc, char *argv[])
{
	struct s_config		config;
	t_pthread_renderer	renderer;
	pthread_t			threads[4];

	if (argc != 2)
	{
		write(STDERR_FILENO, USAGE_PRE, sizeof(USAGE_PRE) - 1);
		write(STDERR_FILENO, argv[0], ft_strlen(argv[0]));
		write(STDERR_FILENO, USAGE_POST, sizeof(USAGE_POST) - 1);
		return (1);
	}
	// TODO: move + error
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	if (read_config(argv[1], &config))
	{
		renderer = create_pthread_renderer(&config.scene, config.size, false);
		pthread_renderer_create_threads(&renderer, threads, sizeof(threads) / sizeof(*threads));
		sdl_frontend(&config, &renderer);
		free_config(&config);
		return (0);
	}
	return (1);
}

bool		load_image(t_image *dst, const char *path) {
	SDL_Surface *surface;

	if (!(surface = IMG_Load(path)))
		return (false);
	if (!(surface = SDL_ConvertSurfaceFormat(surface,
		SDL_PIXELFORMAT_ARGB8888, 0)))
		return (false);
	*dst = (t_image) {
		.size.width = surface->w,
		.size.height = surface->h,
		.pixels = surface->pixels
	};
	return (true);
}

const char	*get_image_error(void) {
	return IMG_GetError();
}

uint32_t	getpixel(t_image *image, size_t x, size_t y)
{
	return (image->pixels[y * image->size.width + x]);
}
