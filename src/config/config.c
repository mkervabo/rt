/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:39:51 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/14 09:18:58 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.h"
#include "config_utils.h"
#include "config.h"
#include "string_utils.h"

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static bool		read_name_and_size(t_toml_table *toml, struct s_config *config)
{
	t_toml	*value;
	double	width;
	double	height;

	if (!(value = table_get(toml, "width")))
		return (false);
	if (!read_digit(value, &width))
		return (false);
	config->size.width = width;
	if (!(value = table_get(toml, "height")))
		return (false);
	if (!read_digit(value, &height))
		return (false);
	config->size.height = height;
	if (!(read_toml_type(toml, &value, "name", TOML_String)))
		return (false);
	config->name = value->value.string_v;
	value->value.string_v = NULL;
	return (true);
}

static void		putnbr_fd(int fd, size_t n)
{
	char		buf[21];
	size_t		i;

	i = sizeof(buf);
	if (!n)
		buf[--i] = '0';
	else
		while (n)
		{
			buf[--i] = (n % 10) + '0';
			n /= 10;
		}
	write(fd, buf + i, sizeof(buf) - i);
}

static bool		print_toml_error(t_reader *r, t_toml_error err,
	const char *file)
{
	char	*msg;

	write(STDERR_FILENO, file, ft_strlen(file));
	write(STDERR_FILENO, ":", 1);
	putnbr_fd(STDERR_FILENO, r->line);
	write(STDERR_FILENO, ":", 1);
	putnbr_fd(STDERR_FILENO, r->column);
	write(STDERR_FILENO, " ", 1);
	msg = toml_error_msg(err);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	return (false);
}

static bool		read_config_scene(struct s_config *config, t_toml_table *toml)
{
	t_toml			*camera;
	t_toml			*video;

	if (!read_name_and_size(toml, config))
		return (config_error(toml, config, "Invalid name or size"));
	if (!(config->scene.objects = read_objects(toml,
		&config->scene.objects_size)))
		return (config_error(toml, config, "Invalid objects"));
	if (!(config->scene.lights = read_lights(toml, &config->scene.lights_size)))
		return (config_error(toml, config, "Invalid lights"));
	if (!read_toml_type(toml, &camera, "camera", TOML_Table)
			|| !(config->scene.camera = read_camera(camera->value.table_v)))
		return (config_error(toml, config, "Invalid camera"));
	if (!(config->scene.filters = read_filters(toml,
		&config->scene.filters_size)))
		return (config_error(toml, config, "Invalid filters"));
	config->video = NULL;
	if (read_toml_type(toml, &video, "video", TOML_Table)
			&& !(config->video = read_video(video->value.table_v)))
		return (config_error(toml, config, "Invalid video"));
	free_toml_table(toml);
	return (true);
}

bool			read_config(t_reader *r, const char *file,
	struct s_config *config)
{
	t_toml_table	*toml;
	t_toml_error	err;

	*config = (struct s_config) { .name = NULL };
	if ((err = read_toml(r, &toml, true)) != No_Error)
		return (print_toml_error(r, err, file));
	if (!read_config_scene(config, toml))
		return (false);
	return (true);
}
