/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   black_and_white.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:44:42 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 14:48:52 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLACK_AND_WHITE_H
# define BLACK_AND_WHITE_H

# include "filter.h"

struct							s_black_and_white_filter
{
	t_filter	super;
};

void							black_and_white_filter(uint32_t *pixels,
								struct s_pixel_hit *hits,
								struct s_size window);
struct s_black_and_white_filter	*read_black_and_white_filter(
								t_toml_table *toml);
void							free_black_and_white_filter(
								struct s_black_and_white_filter *filter);

#endif
