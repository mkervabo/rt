/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon_material_free.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:39:08 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/12 14:39:38 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cartoon_material.h"
#include <stdlib.h>

void						free_cartoon_material(
	struct s_cartoon_material *material)
{
	free_material(material->material);
	free(material);
}
