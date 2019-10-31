/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:38:16 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 17:18:21 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANTI_ALIASING_H
# define ANTI_ALIASING_H

# include "filter.h"

struct							s_anti_aliasing_filter
{
	t_filter	super;
	double		size;
};

void							anti_aliasing_filter(struct
								s_anti_aliasing_filter *aa, uint32_t *pixels,
								struct s_pixel_hit *hits, struct s_size window);
struct s_anti_aliasing_filter	*read_anti_aliasing_filter(t_toml_table *toml);
void							free_anti_aliasing_filter(
								struct s_anti_aliasing_filter *filter);
#endif
