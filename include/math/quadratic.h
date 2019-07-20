/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:00:59 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/07/20 15:08:02 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_QUADRATIC_H
# define MATH_QUADRATIC_H

# include <stdbool.h>

struct	s_quadratic {
	double	a;
	double	b;
	double	c;
};

bool	solve_quadratic(struct s_quadratic fn, double *min, double *max);

#endif
