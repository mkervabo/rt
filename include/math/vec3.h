/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:58:56 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/08/16 15:47:15 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_VEC3_H
# define MATH_VEC3_H

# include <stdbool.h>

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
t_vec3			vec3_addv(t_vec3 a, double v);
t_vec3			vec3_sub(t_vec3 a, t_vec3 b);
t_vec3			vec3_subv(t_vec3 a, double v);
t_vec3			vec3_mult(t_vec3 a, t_vec3 b);
t_vec3			vec3_divv(t_vec3 a, double v);
t_vec3			vec3_cross(t_vec3 a, t_vec3 b);
double			vec3_dot(t_vec3 a, t_vec3 b);
double			vec3_length(t_vec3 v);
t_vec3			vec3_rotate(t_vec3 v, t_vec3 rot);
t_vec3			vec3_invert(t_vec3 v);
bool			vec3_is_zero(t_vec3 a);

#endif
