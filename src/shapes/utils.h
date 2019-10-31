/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:22:03 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/05 15:22:03 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRC_SHAPES_UTILS_H
# define SRC_SHAPES_UTILS_H

# include "toml.h"
# include "shape.h"

bool	read_shape_super(t_toml_table *toml, t_shape *shape);
void	free_shape_super(t_shape *object);

#endif
