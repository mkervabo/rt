/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:39:51 by mkervabo          #+#    #+#             */
/*   Updated: 2019/08/11 15:05:17 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.h"

/*bool		read_window(t_toml_table *toml, t_win *win)
{
	t_toml	*value;
	double	width;
	double	height;

	if (!(value = table_get(toml, "width")))
		return (false);
	if (!read_digit(value, &width))
		return (false);
	win->width = width;
	if (!(value = table_get(toml, "height")))
		return (false);
	if (!read_digit(value, &height))
		return (false);
	win->height = height;
	if (!(read_toml_type(toml, &value, "name", TOML_String)))
		return (false);
	win->name = value->value.string_v;
	value->value.string_v = NULL;
	return (true);
}

t_light		**read_lights(t_toml_table *toml, size_t *size)
{
	t_light		**lights;
	t_toml		*v;
	size_t		i;

	if (read_toml_type(toml, &v, "lights", TOML_Array) == false)
		return (NULL);
	if (v->value.array_v->len == 0
		|| v->value.array_v->inner[0].type != TOML_Table)
		return (NULL);
	*size = v->value.array_v->len;
	if (!(lights = malloc(sizeof(t_light*) * *size)))
		return (NULL);
	i = 0;
	while (i < *size)
	{
		if (!(lights[i] = read_light(v->value.array_v->inner[i].value.table_v)))
			return (free_ptr_array((void **)lights, i));
		i++;
	}
	return (lights);
}

bool		read_camera(t_toml_table *toml, t_cam *cam)
{
	t_toml	*camera;
	t_toml	*value;

	if (!read_toml_type(toml, &camera, "camera", TOML_Table))
		return (false);
	if (!read_toml_type(camera->value.table_v, &value, "position", TOML_Table))
		return (false);
	if (!read_t_vec3(value->value.table_v, &cam->pos))
		return (false);
	if (!read_toml_type(camera->value.table_v, &value, "rotation", TOML_Table))
		return (false);
	if (!read_t_vec3(value->value.table_v, &cam->rot))
		return (false);
	cam->rot = vec3_multv(cam->rot, M_PI / 180);
	return (true);
}*/

#include "config.h"
#include "toml.h"

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static t_shape	**read_objects(t_toml_table *toml, size_t *size)
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

static bool		print_toml_error(t_reader *r, t_toml_error err, char *file)
{
	char	*msg;

	write(STDERR_FILENO, file, strlen(file));
	write(STDERR_FILENO, ":", 1);
	putnbr_fd(STDERR_FILENO, r->line);
	write(STDERR_FILENO, ":", 1);
	putnbr_fd(STDERR_FILENO, r->column);
	write(STDERR_FILENO, " ", 1);
	msg = toml_error_msg(err);
	write(STDERR_FILENO, msg, strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	return (false);
}

bool	read_config(const char *file, struct s_config *config)
{
	int			fd;
	t_reader	r;
	t_toml_table	*toml;
	t_toml			*camera;
	t_toml_error	err;
	char			buffer[4096];

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		perror("rt");
		return (false);
	}
	*config = (struct s_config) {
		.name = "Unicorn",
		.size = { 1024, 960 }
	};
	r = create_reader(fd, buffer, sizeof(buffer));
	if ((err = read_toml(&r, &toml, true)) != No_Error)
		return (print_toml_error(&r, err, file));
	close(fd);
	if (!(config->scene.objects = read_objects(toml, &config->scene.objects_size)))
	{
		write(STDERR_FILENO, "Invalid objects\n", sizeof("Invalid objects\n") - 1);
		return (false);
	}
	if (!read_toml_type(toml, &camera, "camera", TOML_Table)
			|| !(config->scene.camera = read_camera(camera->value.table_v)))
	{
		write(STDERR_FILENO, "Invalid camera\n", sizeof("Invalid camera\n") - 1);
		return (false);
	}
	return (true);
}

void	free_config(struct s_config *config)
{
	// TODO
}
