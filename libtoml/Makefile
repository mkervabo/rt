# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/12 13:29:47 by mkervabo          #+#    #+#              #
#    Updated: 2019/05/19 15:17:42 by mkervabo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = libtoml.a
CC     = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g

include src.mk

OBJS=$(patsubst src/%.c,build/%.o,$(SRCS))

all: $(NAME)

build/%.o: src/%.c include/toml.h Makefile
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -rf build

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all	clean fclean re
