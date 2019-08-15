/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:58:56 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/08/15 13:28:56 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_VEC3_H
# define MATH_VEC3_H

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

t_vec3			vec3(double x, double y, double z);
t_vec3			vec3_multv(t_vec3 a, double v);
t_vec3			vec3_unit(t_vec3 v);
t_vec3			vec3_add(t_vec3 a, t_vec3 b);
t_vec3			vec3_sub(t_vec3 a, t_vec3 b);
t_vec3			vec3_mult(t_vec3 a, t_vec3 b);
t_vec3			vec3_divv(t_vec3 a, double v);
t_vec3			vec3_cross(t_vec3 a, t_vec3 b);
double			vec3_dot(t_vec3 a, t_vec3 b);
double			vec3_length(t_vec3 v);
t_vec3			vec3_rotate(t_vec3 v, t_vec3 rot);
t_vec3			vec3_invert(t_vec3 v);

#endif
