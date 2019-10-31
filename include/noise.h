/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:37:03 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/05 14:37:13 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOISE_H
# define NOISE_H

# include "math/vec3.h"

double	noise(t_vec3 p);
double	turbulence(t_vec3 p);

#endif
