/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:51:16 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/11/08 18:48:51 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

typedef struct	s_color {
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}				t_color;

uint32_t		color_to_rgb(t_color color);
t_color 		color_from_rgb(uint32_t color);

t_color			color_add(t_color a, t_color b);
t_color			color_ratio(t_color a, t_color b);
t_color			color_multv(t_color c, double v);

#endif
