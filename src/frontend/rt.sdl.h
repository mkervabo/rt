/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.sdl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 19:37:04 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/13 20:01:16 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SDL_H
# define RT_SDL_H

# include "config.h"

# include <SDL.h>
# include <stdbool.h>
# include <stdlib.h>

struct	s_sdl_window
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Texture		*screen;
	size_t			width;
	bool			quit;
};

void	poll_events(struct s_sdl_window *window, bool wait);
bool	update_render(uint32_t *pixels, void *user);
void	render_frames(struct s_config *config, struct s_sdl_window *window,
	uint32_t **pixels, size_t nframes);
void	render_video(struct s_config *config, struct s_sdl_window *window,
	uint32_t **pixels, size_t nframes);

#endif
