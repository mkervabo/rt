/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:14:44 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/10/26 16:31:59 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_TYPE_H
# define LIGHT_TYPE_H

enum e_light_type {
	LIGHT_POINT,
	LIGHT_AMBIENT,
	LIGHT_DIRECTIONAL,
	LIGHT_SPOT
};

#endif
