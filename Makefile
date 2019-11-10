# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/12 13:29:47 by mkervabo          #+#    #+#              #
#    Updated: 2019/11/06 15:31:03 by mkervabo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all
.SECONDARY:

PKG_CONFIG ?= pkg-config
INSTALL ?= install

rt.rootdir := $(dir $(lastword $(MAKEFILE_LIST)))

ifndef V
clean::
	@echo "  CLEAN"
fclean::
	@echo "  FCLEAN"
endif

include $(rt.rootdir)lib/toml/Makefile
include $(rt.rootdir)lib/obj/Makefile

rt.srcs :=
include src.mk

rt.objects := $(rt.srcs:.c=.o)
rt.objects := $(filter-out src/frontend/%, $(rt.objects))
rt.objects := $(addprefix $(rt.rootdir), $(rt.objects))

rt.sdl.o $(rt.objects): CC       = gcc
rt.sdl.o $(rt.objects): CFLAGS   ?= -Wall -Wextra
rt.sdl.o $(rt.objects): CPPFLAGS += -MMD -MP -I$(rt.rootdir)include
rt.sdl.o $(rt.objects): CPPFLAGS += -I$(libtoml.rootdir)include -I$(libobj.rootdir)include 
rt.sdl.o: CPPFLAGS += $(shell $(PKG_CONFIG) --cflags sdl2 SDL2_image)

rt.sdl: LDLIBS += $(shell $(PKG_CONFIG) --libs sdl2 SDL2_image) -lm -lpthread

.PHONY: all
all: rt

vpath %.c $(rt.rootdir)src/frontend

rt.sdl: rt.sdl.o $(rt.objects) libtoml.a libobj.a

rt: rt.sdl
	$(INSTALL) -m 777 $< $@

.PHONY: clean
clean:: rt.objects += rt.sdl.o
clean::
	$(RM) $(rt.objects:.o=.{o,d,gcno,gcna})

.PHONY: fclean
fclean:: clean
	$(RM) -r rt rt.sdl

.PHONY: re
re: fclean all

ARFLAGS = rcs

-include $(wildcard $(rt.rootdir)src/*.d $(rt.rootdir)src/*/*.d)

ifndef V
  $(eval COMPILE.c = @echo "  CC      $$(@F)"; $(value COMPILE.c))
  $(eval        AR = @echo "  AR      $$(@F)"; $(value AR))
  $(eval    LINK.o = @echo "  LD      $$(@F)"; $(value LINK.o))
  $(eval   INSTALL = @echo "  INSTALL $$(@F)"; $(value INSTALL))
  $(eval        RM = @$(value RM))
endif
