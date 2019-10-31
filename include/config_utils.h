/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:34:35 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/05 14:34:44 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_UTILS_H
# define CONFIG_UTILS_H

# include "toml.h"
# include "math/vec3.h"
# include "color.h"
# include <stdbool.h>

bool	read_digit(t_toml *toml, double *digit);
bool	read_vec3(t_toml_table *toml, t_vec3 *vec);
bool	read_color(t_toml_table *toml, t_color *color);
bool	read_toml_type(t_toml_table *toml, t_toml **value, char *name,
	enum e_toml_type type);
void	*rt_error(void *ptr, const char *msg);
void	*nfree(void *ptr);

#endif
