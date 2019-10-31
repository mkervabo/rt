/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:41:06 by gfranco           #+#    #+#             */
/*   Updated: 2019/11/06 11:41:08 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "toml.h"
# include "shape.h"
# include "material.h"
# include <stdbool.h>

typedef struct	s_object
{
	struct s_shape			*shape;
	struct s_material		*material;
}				t_object;

bool			read_object(t_object *obj, t_toml_table *toml);
t_object		*read_objects(t_toml_table *toml, size_t *size);

#endif
