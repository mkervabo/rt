/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:05:55 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 14:52:10 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILTER_H
# define FILTER_H

# include "toml.h"
# include "math/size.h"
# include "object.h"
# include <stdint.h>

typedef struct s_scene	t_scene;

typedef struct			s_filter
{
	uint8_t		type;
}						t_filter;

struct					s_pixel_hit
{
	double				t;
	struct s_object		*who;
};

t_filter				**read_filters(t_toml_table *toml, size_t *size);
void					apply_filter(t_filter *filter, uint32_t *pixels,
		struct s_pixel_hit *hits, struct s_size window);
void					apply_video_filter(t_filter *filter, uint32_t **pixels,
		size_t *nframes, struct s_size window);
void					free_filter(t_filter *filter);

#endif
