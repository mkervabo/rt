/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:14:44 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/11/04 19:24:10 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_TYPES_H
# define LIGHT_TYPES_H

enum	e_light_type
{
	LIGHT_POINT,
	LIGHT_AMBIENT,
	LIGHT_DIRECTIONAL,
	LIGHT_SPOT
};

#endif
