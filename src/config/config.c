/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:39:51 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/10 18:02:21 by mkervabo         ###   ########.fr       */
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

t_object		*read_objects(t_toml_table *toml, size_t *size)
{
	t_object		*objs;
	t_toml			*v;
	size_t			i;

	if (read_toml_type(toml, &v, "objects", TOML_Array) == false)
		return (NULL);
	if (v->value.array_v->len == 0
		|| v->value.array_v->inner[0].type != TOML_Table)
		return (NULL);
	*size = v->value.array_v->len;
	if (!(objs = malloc(sizeof(t_object) * *size)))
		return (NULL);
	i = 0;
	while (i < *size)
	{
		if (!read_object(objs + i, v->value.array_v->inner[i].value.table_v))
			//return (free_ptr_array((void **)objs, i));
			return (NULL);
		i++;
	}
	return (objs);
}

static t_light		**read_lights(t_toml_table *toml, size_t *size)
{
	t_light		**lights;
	t_toml		*v;
	size_t		i;

	if (read_toml_type(toml, &v, "lights", TOML_Array)) {
		if (v->value.array_v->len != 0
			&& v->value.array_v->inner[0].type != TOML_Table)
			return (NULL);
		*size = v->value.array_v->len;
	} else
		*size = 0;
	if (!(lights = malloc(sizeof(t_light*) * *size)))
		return (NULL);
	i = 0;
	while (i < *size)
	{
		if (!(lights[i] = read_light(v->value.array_v->inner[i].value.table_v)))
			//return (free_ptr_array((void **)lights, i));
			return (NULL);
		i++;
	}
	return (lights);
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

static bool		print_toml_error(t_reader *r, t_toml_error err, const char *file)
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

bool	read_config(const char *file, struct s_config *config)
{
	int				fd;
	t_reader		r;
	t_toml_table	*toml;
	t_toml			*camera;
	t_toml_error	err;
	char			buffer[4096];
	t_toml			*video;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		perror("rt");
		return (false);
	}
	r = create_reader(fd, buffer, sizeof(buffer));
	if ((err = read_toml(&r, &toml, true)) != No_Error)
		return (print_toml_error(&r, err, file));
	close(fd);
	if (!read_name_and_size(toml, config)) {
		write(STDERR_FILENO, "Invalid name or size\n", sizeof("Invalid name or size\n") - 1);
		return (false);
	}
	if (!(config->scene.objects = read_objects(toml, &config->scene.objects_size)))
	{
		write(STDERR_FILENO, "Invalid objects\n", sizeof("Invalid objects\n") - 1);
		return (false);
	}
	if (!(config->scene.lights = read_lights(toml, &config->scene.lights_size)))
	{
		write(STDERR_FILENO, "Invalid lights\n", sizeof("Invalid lights\n") - 1);
		return (false);
	}
	if (!read_toml_type(toml, &camera, "camera", TOML_Table)
			|| !(config->scene.camera = read_camera(camera->value.table_v)))
	{
		write(STDERR_FILENO, "Invalid camera\n", sizeof("Invalid camera\n") - 1);
		return (false);
	}
	if (!(config->scene.filters = read_filters(toml, &config->scene.filters_size)))
	{
		write(STDERR_FILENO, "Invalid filters\n", sizeof("Invalid filters\n") - 1);
		return (false);
	}
	config->video = NULL;
	if (read_toml_type(toml, &video, "video", TOML_Table)
			&& !(config->video = read_video(video->value.table_v)))
	{
		write(STDERR_FILENO, "Invalid video\n", sizeof("Invalid video\n") - 1);
		return (false);
	}
	free_toml_table(toml);
	return (true);
}

void	free_config(struct s_config *config)
{
	(void)config;
	// TODO
}
