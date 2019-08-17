/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:58:56 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/08/14 10:35:29 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_VEC2_H
# define MATH_VEC2_H

typedef struct	s_vec2
{
	double		x;
	double		y;
}				t_vec2;

t_vec2			vec2(double x, double y);
t_vec2			vec2_add(t_vec2 a, t_vec2 b);
t_vec2			vec2_sub(t_vec2 a, t_vec2 b);
t_vec2			vec2_mult(t_vec2 a, t_vec2 b);
double			vec2_dot(t_vec2 a, t_vec2 b);

#endif
