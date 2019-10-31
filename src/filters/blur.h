/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:15:09 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 14:49:03 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLUR_H
# define BLUR_H

# include "filter.h"

struct					s_blur_filter
{
	t_filter	super;
	double		size;
};

void					blur_filter(struct s_blur_filter *blur,
						uint32_t *pixels, struct s_pixel_hit *hits,
						struct s_size window);
struct s_blur_filter	*read_blur_filter(t_toml_table *toml);
void					free_blur_filter(struct s_blur_filter *filter);

#endif
