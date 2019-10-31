/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_material_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:41:10 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/12 14:41:47 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xor_material.h"
#include <stdlib.h>

void						free_xor_material(struct s_xor_material *material)
{
	free(material);
}
