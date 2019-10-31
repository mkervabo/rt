/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:31:14 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/11 17:31:54 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_UTILS_H
# define LIGHTS_UTILS_H

# include "toml.h"
# include "light.h"

bool	read_light_super(t_toml_table *toml, t_light *light);
void	free_light_super(t_light *light);

#endif
