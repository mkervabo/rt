/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 14:05:01 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/25 15:38:34 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "toml.h"

static t_object		*read_plane(t_toml_table *toml)
{
	t_object	*plane;

	(void)toml;
	if (!(plane = malloc(sizeof(t_object))))
		return (NULL);
	if (!read_super(toml, plane))
		return (nfree(plane));
	plane->type = Type_Plane;
	read_transparency(toml, &plane->n);
	return (plane);
}

static t_cone		*read_cone(t_toml_table *toml)
{
	t_cone	*cone;
	t_toml	*angle;
	t_toml	*revolution;

	if (!(cone = malloc(sizeof(t_cone))))
		return (NULL);
	if (!(angle = table_get(toml, "angle")))
		return (nfree(cone));
	if (!read_super(toml, &cone->super) || !read_digit(angle, &cone->angle))
		return (nfree(cone));
	if ((revolution = table_get(toml, "revolution")))
	{
		if (revolution->type != TOML_Boolean)
			return (nfree(cone));
		cone->revolution = revolution->value.boolean_v;
	}
	else
		cone->revolution = true;
	cone->angle *= M_PI / 180;
	cone->super.type = Type_Cone;
	read_transparency(toml, &cone->super.n);
	return (cone);
}

static t_cylinder	*read_cylinder(t_toml_table *toml)
{
	t_cylinder	*cylinder;
	t_toml		*radius;

	if (!(cylinder = malloc(sizeof(t_cylinder))))
		return (NULL);
	if (!(radius = table_get(toml, "radius")))
		return (nfree(cylinder));
	if (!read_super(toml, &cylinder->super))
		return (nfree(cylinder));
	if (read_digit(radius, &cylinder->r) == false)
		return (nfree(cylinder));
	cylinder->super.type = Type_Cylinder;
	read_transparency(toml, &cylinder->super.n);
	return (cylinder);
}

static t_sphere		*read_sphere(t_toml_table *toml)
{
	t_sphere	*sphere;
	t_toml		*radius;

	if (!(sphere = malloc(sizeof(t_sphere))))
		return (NULL);
	if (!(radius = table_get(toml, "radius")))
		return (nfree(sphere));
	if (!read_super(toml, &sphere->super))
		return (nfree(sphere));
	if (read_digit(radius, &sphere->r) == false)
		return (nfree(sphere));
	sphere->super.type = Type_Sphere;
	read_transparency(toml, &sphere->super.n);
	return (sphere);
}

t_object			*read_object(t_toml_table *toml)
{
	t_toml	*type;

	if (!(type = table_get(toml, "type")))
		return (NULL);
	if (type->type != TOML_String)
		return (NULL);
	if (ft_strcmp(type->value.string_v, "SPHERE") == 0)
		return ((t_object *)read_sphere(toml));
	if (ft_strcmp(type->value.string_v, "CYLINDER") == 0)
		return ((t_object *)read_cylinder(toml));
	if (ft_strcmp(type->value.string_v, "PLANE") == 0)
		return ((t_object *)read_plane(toml));
	if (ft_strcmp(type->value.string_v, "CONE") == 0)
		return ((t_object *)read_cone(toml));
	else
		return (NULL);
}
