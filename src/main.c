/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:27:39 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/07/20 17:56:24 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "frontend/sdl.h"
#include <unistd.h>

static size_t ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

#define USAGE_PRE "Usage: "
#define USAGE_POST " [scene.toml]\n"

int	main(int argc, char *argv[])
{
	struct s_config	config;

	if (argc != 2)
	{
		write(STDERR_FILENO, USAGE_PRE, sizeof(USAGE_PRE) - 1);
		write(STDERR_FILENO, argv[0], ft_strlen(argv[0]));
		write(STDERR_FILENO, USAGE_POST, sizeof(USAGE_POST) - 1);
		return (1);
	}
	if (read_config(argv[1], &config))
	{
		sdl_frontend(&config);
		free_config(&config);
		return (0);
	}
	return (1);
}
