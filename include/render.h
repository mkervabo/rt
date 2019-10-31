/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:38:43 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/13 20:31:04 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "math/size.h"
# include "scene.h"
# include <stdint.h>
# include <stdbool.h>
# include <stdatomic.h>

struct			s_thread_arg {
	uint32_t			*pixels;
	struct s_pixel_hit	*hits;
	t_scene				*scene;
	struct s_size		window;
	atomic_size_t		i;
	size_t				done;
};

typedef bool	(*t_update_fn)(uint32_t *pixels, void *user);

uint32_t		*render(t_scene *scene, struct s_size window,
	t_update_fn update, void *user);
#endif
