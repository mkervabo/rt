/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_union.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 13:30:56 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/22 16:37:03 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "toml.h"

t_union			*read_union(t_toml_table *toml)
{
	t_union		*unions;
	t_toml		*value;

	if (!(unions = malloc(sizeof(t_union))))
		return (NULL);
	unions->super.color = (t_color){ 0, 0, 0 };
	unions->super.light = Light_Diffuse;
	if (!read_super_p_r(toml, (t_object*)unions))
		return (false);
	if (!(value = table_get(toml, "first")))
		return (nfree(unions));
	if ((unions->first = read_object(value->value.table_v)) == NULL)
		return (nfree(unions));
	if (!(value = table_get(toml, "second")))
		return (nfree(unions));
	if ((unions->second = read_object(value->value.table_v)) == NULL)
		return (nfree(unions));
	unions->super.type = Type_Union;
	return (unions);
}

t_intersec		*read_intersection(t_toml_table *toml)
{
	t_intersec		*intersection;
	t_toml			*value;


	if (!(intersection = malloc(sizeof(t_intersec))))
		return (NULL);
	intersection->super.color = (t_color){ 0, 0, 0 };
	intersection->super.light = Light_Diffuse;
	if (!read_super_p_r(toml, (t_object*)intersection))
		return (false);
	if (!(value = table_get(toml, "first")))
		return (nfree(intersection));
	if ((intersection->first = read_object(value->value.table_v)) == NULL)
		return (nfree(intersection));
	if (!(value = table_get(toml, "second")))
		return (nfree(intersection));
	if ((intersection->second = read_object(value->value.table_v)) == NULL)
		return (nfree(intersection));
	intersection->super.type = Type_Intersection;
	return (intersection);
}

t_minus			*read_minus(t_toml_table *toml)
{
	t_minus		*minus;
	t_toml		*value;

	if (!(minus = malloc(sizeof(t_minus))))
		return (NULL);
	minus->super.color = (t_color){ 0, 0, 0 };
	minus->super.light = Light_Diffuse;
	if (!read_super_p_r(toml, (t_object*)minus))
		return (false);
	if (!(value = table_get(toml, "first")))
		return (nfree(minus));
	if ((minus->first = read_object(value->value.table_v)) == NULL)
		return (nfree(minus));
	if (!(value = table_get(toml, "second")))
		return (nfree(minus));
	if ((minus->second = read_object(value->value.table_v)) == NULL)
		return (nfree(minus));
	minus->super.type = Type_Minus;
	return (minus);
}