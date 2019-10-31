/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:34:56 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/12 14:49:53 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "math/size.h"
# include "scene.h"
# include "camera.h"
# include "video.h"

struct	s_config
{
	char			*name;
	struct s_size	size;
	t_scene			scene;
	t_video			*video;

};

void	free_config(struct s_config *config);
bool	read_config(const char *file, struct s_config *config);
void	free_config(struct s_config *config);
void	*free_light_array(t_light **lights, size_t len);
void	*free_object_array(t_object *objects, size_t len);
void	*free_filter_array(t_filter **filters, size_t len);
bool	config_error(t_toml_table *toml, struct s_config *config,
		const char *msg);

#endif
