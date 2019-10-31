/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:32:42 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 17:19:00 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPIA_H
# define SEPIA_H

# include "filter.h"

struct					s_sepia_filter
{
	t_filter	super;
};

void					sepia_filter(uint32_t *pixels, struct s_pixel_hit *hits,
						struct s_size window);
struct s_sepia_filter	*read_sepia_filter(t_toml_table *toml);
void					free_sepia_filter(struct s_sepia_filter *filter);

#endif
