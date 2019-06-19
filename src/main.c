/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:39:35 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/19 14:21:05 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "toml.h"
#include <fcntl.h>
#include <unistd.h>

size_t			ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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

static int		print_toml_error(t_reader *r, t_toml_error err, char *file)
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
	return (1);
}

int				main(int argc, char *argv[])
{
	t_reader		r;
	t_toml_table	*toml;
	int				fd;
	t_toml_error	err;
	char			buffer[4096];

	if (argc != 2)
	{
		write(STDERR_FILENO, USAGE_PRE, sizeof(USAGE_PRE) - 1);
		write(STDERR_FILENO, argv[0], ft_strlen(argv[0]));
		write(STDERR_FILENO, USAGE_POST, sizeof(USAGE_POST) - 1);
		return (1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		write(STDERR_FILENO, ERR_INVALID_FILE, sizeof(ERR_INVALID_FILE) - 1);
		return (1);
	}
	r = create_reader(fd, buffer, sizeof(buffer));
	if ((err = read_toml(&r, &toml, true)) != No_Error)
		return (print_toml_error(&r, err, argv[1]));
	close(fd);
	render_scene(toml);
	return (0);
}
