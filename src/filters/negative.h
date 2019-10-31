/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:30:40 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 17:18:58 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEGATIVE_H
# define NEGATIVE_H

# include "filter.h"

struct						s_negative_filter
{
	t_filter	super;
};

void						negative_filter(uint32_t *pixels,
							struct s_pixel_hit *hits, struct s_size window);
struct s_negative_filter	*read_negative_filter(t_toml_table *toml);
void						free_negative_filter(
							struct s_negative_filter *filter);
#endif
