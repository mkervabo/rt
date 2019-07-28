# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/19 11:46:19 by mkervabo          #+#    #+#              #
#    Updated: 2019/07/20 18:18:19 by dde-jesu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt
CC = gcc

LIBS = toml obj mtl
LIBS_DIR = $(patsubst %, lib/%/, $(LIBS))
LIBS_FILES = $(patsubst %, lib%.a, $(LIBS))
LIBS_FULL_FILES = $(join $(LIBS_DIR), $(LIBS_FILES))

CFLAGS = -Wall -Wextra -I./include $(patsubst %, -I%/include, $(LIBS_DIR)) $(shell pkg-config --cflags sdl2 SDL2_image) -g
LDFLAGS = $(patsubst %, -L%, $(LIBS_DIR)) $(patsubst %, -l%, $(LIBS)) $(shell pkg-config --libs sdl2 SDL2_image) -lm

include src.mk

OBJS=$(patsubst src/%.c,build/%.o,$(SRCS))

all: $(NAME)

# Special rule to force exec
phony:
.PHONY: phony

$(LIBS_FULL_FILES): phony
	$(MAKE) --no-print-directory -C $(dir $@)

build/%.o: src/%.c include/*.h Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJS) $(LIBS_FULL_FILES)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -rf build

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
