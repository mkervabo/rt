/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_contrast.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:22:43 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/11 17:18:43 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEPTH_CONTRAST_H
# define DEPTH_CONTRAST_H

# include "filter.h"

struct							s_depth_contrast_filter
{
	t_filter	super;
};

void							depth_contrast_filter(
								struct s_depth_contrast_filter *filter,
								uint32_t *pixels,
								struct s_pixel_hit *hits,
								struct s_size window);
struct s_depth_contrast_filter	*read_depth_contrast_filter(t_toml_table *toml);
void							free_depth_contrast_filter(
								struct s_depth_contrast_filter *filter);

#endif
