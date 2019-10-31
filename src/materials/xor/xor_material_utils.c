/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_material_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:43:02 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/12 14:43:41 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xor_material.h"
#include "shape.h"

double						xor_material_transparency(
	struct s_xor_material *material, struct s_hit *hit)
{
	(void)material;
	(void)hit;
	return (0.0);
}
