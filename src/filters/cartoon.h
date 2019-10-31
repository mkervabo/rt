/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:16:45 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 14:49:23 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CARTOON_H
# define CARTOON_H

# include "filter.h"

struct					s_cartoon_filter
{
	t_filter	super;
	t_color		color;
};

void					cartoon_filter(struct s_cartoon_filter *filter,
						uint32_t *pixels, struct s_pixel_hit *hits,
						struct s_size window);
struct s_cartoon_filter	*read_cartoon_filter(t_toml_table *toml);
void					free_cartoon_filter(struct s_cartoon_filter *filter);

#endif
