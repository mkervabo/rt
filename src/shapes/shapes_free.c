/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:40:18 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/12 14:01:20 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_shape.h"
#include "cone.h"
#include "paraboloid.h"
#include "utils.h"
#include <stdlib.h>

void		free_obj_shape(struct s_obj_shape *obj)
{
	free_shape_super(&obj->super);
	free(obj->triangles);
	free(obj);
}

void		free_cone(struct s_cone *cone)
{
	free_shape_super(&cone->super);
	free(cone);
}

void		free_paraboloid(struct s_paraboloid *paraboloid)
{
	free_shape_super(&paraboloid->super);
	free(paraboloid);
}
