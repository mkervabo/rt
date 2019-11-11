/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.worker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 13:49:05 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/11/10 15:03:06 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "image.h"
#include "renderers/pthread.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_TILES 4

struct s_rendering_ctx {
	int					fd;
	uint16_t			start_tile;
	t_pthread_renderer	*renderer;
};

static size_t min(size_t a, size_t b)
{
	return (a < b ? a : b);
}

static void send_tile(struct s_rendering_ctx *ctx, uint32_t *pixels, size_t x, size_t y)
{
	size_t			sub_y;

	sub_y = 0;
	while (sub_y < TILE_SIZE && y * TILE_SIZE + sub_y < ctx->renderer->w.height)
	{
		write(ctx->fd,
			pixels + (y * TILE_SIZE + sub_y) * ctx->renderer->w.width + x * TILE_SIZE,
			min(TILE_SIZE, ctx->renderer->w.width - x * TILE_SIZE) * 4);
		sub_y++;
	}
}

bool	handle_rendering_update(uint32_t *pixels, size_t tiles_done, void *user)
{
	struct s_rendering_ctx	*const ctx = user;
	size_t					i;
	uint16_t				tile;

	if (tiles_done == ctx->start_tile + NUM_TILES)
	{
		i = 0;
		while (i < NUM_TILES)
		{
			write(ctx->fd, (uint8_t []) {0x01}, 1);
			tile = ctx->start_tile + i;
			write(ctx->fd, &tile, sizeof(tile));
			send_tile(ctx,
				pixels,
				tile % ((ctx->renderer->w.width + ctx->renderer->w.width - 1) / TILE_SIZE),
				tile / ((ctx->renderer->w.width + ctx->renderer->w.width - 1) / TILE_SIZE)
			);
			i++;
		}
		write(ctx->fd, (uint8_t []) {0x00, NUM_TILES}, 2);
		if (read(ctx->fd, &ctx->start_tile, sizeof(ctx->start_tile)) != sizeof(ctx->start_tile))
			return (true);
		atomic_store(&ctx->renderer->last_tile, ctx->start_tile);
		atomic_store(&ctx->renderer->tiles_done, ctx->start_tile);
		i = 0;
		printf("Launch\n");
		while (i < NUM_TILES)
		{
			pthread_render_continue(ctx->renderer);
			i++;
		}
	}
	return (false);
}

void	handle_rendering_work(int fd, struct s_config *config)
{
	t_pthread_renderer		renderer;
	pthread_t				threads[NUM_TILES];
	struct s_rendering_ctx	ctx;

	config->scene.filters_size = 0;
	ctx = (struct s_rendering_ctx) { .fd = fd, .renderer = &renderer };
	renderer = create_pthread_renderer(&config->scene, config->size, false, true);
	pthread_renderer_create_threads(&renderer, threads, sizeof(threads) / sizeof(*threads));

	write(fd, (uint8_t []) {0x00, NUM_TILES}, 2);
	if (read(fd, &ctx.start_tile, sizeof(ctx.start_tile)) != sizeof(ctx.start_tile))
		return ;

	atomic_store(&renderer.last_tile, ctx.start_tile);
	renderer.tiles_done = ctx.start_tile;

	printf("Render\n");
	free(pthread_render(&renderer, handle_rendering_update, &ctx));
}

static int g_client_fd;

void	handle_client(int fd)
{
	uint16_t		len;
	char			*config_data;
	struct s_config	config;
	t_reader		r;

	if (read(fd, &len, sizeof(len)) != sizeof(len))
	{
		perror("read");
		return ;
	}
	if (!(config_data = malloc(len)))
	{
		perror("malloc");
		return ;
	}
	if (read(fd, config_data, len) != len)
	{
		perror("read");
		return ;
	}
	printf("%.*s", len, config_data);
	r = create_reader(-1, config_data, len);
	r.len = len;
	g_client_fd = fd;
	if (read_config(&r, "config", &config))
		handle_rendering_work(fd, &config);
	else
		printf("Config error\n");
}

int		main(int argc, char *argv[])
{
	int	server_fd;
	int	client_fd;
	struct sockaddr_in client;
	socklen_t len;

	server_fd = socket(AF_INET, SOCK_STREAM, 0); 

	if (bind(server_fd, (struct sockaddr *)&(struct sockaddr_in) { .sin_family = AF_INET, .sin_port = 4242 }, sizeof(struct sockaddr_in)) != 0)
	{
		perror("bind");
		return (1);
	}

	if (listen(server_fd, 1) != 0)
	{
		perror("listen");
		return (1);
	}

	printf("Listening on 4242\n");
	while (true)
	{
		len = sizeof(struct sockaddr_in);
		client_fd = accept(server_fd, (struct sockaddr *)&client, &len); 

		printf("Client\n");
		handle_client(client_fd);
		close(client_fd);
	}
}

bool		load_image(t_image *dst, const char *path) {
	uint8_t		op;
	uint16_t	len;

	op = 0x02;
	write(g_client_fd, &op, sizeof(op));
	len = strlen(path);
	write(g_client_fd, &len, sizeof(len));
	write(g_client_fd, path, len);
	if (read(g_client_fd, &dst->size.width, sizeof (dst->size.width)) != sizeof(dst->size.width))
		return (false);
	if (read(g_client_fd, &dst->size.height, sizeof(dst->size.height)) != sizeof(dst->size.height))
		return (false);
	if (!(dst->pixels = malloc(dst->size.width * dst->size.height * 4)))
		return (false);
	if (read(g_client_fd, dst->pixels, dst->size.width * dst->size.height) != dst->size.width * dst->size.height)
		return (false);
	return (true);
}

const char	*get_image_error(void) {
	return "Image Error";
}

uint32_t	getpixel(t_image *image, size_t x, size_t y)
{
	return (image->pixels[y * image->size.width + x]);
}
