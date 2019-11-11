#include "renderers/network.h"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define TILE_SIZE 96

static void		*ft_memset(void *s, int c, size_t n)
{
	while (n--)
		((unsigned char *)s)[n] = c;
	return (s);
}

static size_t min(size_t a, size_t b)
{
	return (a < b ? a : b);
}

uint32_t			*network_render(struct s_config *config, t_update_fn update, void *user)
{
	uint32_t			*pixels;
	struct sockaddr_in	workers[] = {
		{ .sin_family = AF_INET, .sin_addr.s_addr = inet_addr("127.0.0.1"), .sin_port = 4242 }
	};
	size_t				num_workers = 1;
	size_t				i;
	int					fd;
	int					config_fd;
	uint16_t			config_len;
	fd_set				fds;
	fd_set				read_fds;
	char				buffer[4096];
	ssize_t				len;
	uint16_t			last_tile;

	FD_ZERO(&fds);	
	i = 0;
	config_fd = open(config->file, O_RDONLY);
	config_len = lseek(config_fd, 0, SEEK_END);

	while (i < num_workers)
	{
		fd = socket(AF_INET, SOCK_STREAM, 0); 

		if (connect(fd, (struct sockaddr *)workers + i, sizeof(*workers)) != 0)
		{
			perror("connect");
			return (NULL);
		}

		lseek(config_fd, 0, SEEK_SET);
		
		write(fd, &config_len, sizeof(config_len));
		while ((len = read(config_fd, buffer, 4096)) > 0)
			write(fd, buffer, len);

		FD_SET(fd, &fds);
		i++;
	}

	if (!(pixels = malloc(sizeof(uint32_t) * config->size.width * config->size.height)))
		return (NULL);
	ft_memset(pixels, 0, sizeof(uint32_t) * config->size.width * config->size.height);

	last_tile = 0;
	size_t tiles = ((config->size.width + config->size.width - 1) / TILE_SIZE)
			* ((config->size.height + config->size.height - 1) / TILE_SIZE);
	while (last_tile < tiles)
	{
		read_fds = fds;
		if (select(FD_SETSIZE, &read_fds, NULL, NULL, NULL) < 0)
		{
			perror("select");
			free(pixels);
			return (NULL);
		}

		i = 0;
		while (i < FD_SETSIZE)
		{
			if (FD_ISSET(i, &read_fds))
			{
				fd = i;
				uint8_t op;

				read(fd, &op, sizeof(op));
				if (op == 0x00)
				{
					uint8_t num_tiles;
					read(fd, &num_tiles, sizeof(num_tiles));
					write(fd, &last_tile, sizeof(last_tile));
					last_tile += num_tiles;
				}
				else if (op == 0x01)
				{
					printf("Op 1 %d\n", fd);
					uint16_t tile;
					read(fd, &tile, sizeof(tile));
					printf("Tile %u\n", tile);
					size_t x = tile % ((config->size.width + config->size.width - 1) / TILE_SIZE);
					size_t y = tile / ((config->size.width + config->size.width - 1) / TILE_SIZE);

					size_t sub_y;
					sub_y = 0;
					while (sub_y < TILE_SIZE && y * TILE_SIZE + sub_y < config->size.height)
					{
						read(fd,
							pixels + (y * TILE_SIZE + sub_y) * config->size.width + x * TILE_SIZE,
							min(TILE_SIZE, config->size.width - x * TILE_SIZE) * 4);
						sub_y++;
					}
					update(pixels, user);
				}
				else
					printf("unknown op %x %d\n", op, fd);
			}
			i++;
		}
	}

	return (pixels);
}
