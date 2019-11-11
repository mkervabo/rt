# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/12 13:29:47 by mkervabo          #+#    #+#              #
#    Updated: 2019/11/13 18:53:35 by dde-jesu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all
.SECONDARY:

CC = gcc
CFLAGS = -Wall -Wextra

PKG_CONFIG ?= pkg-config
INSTALL ?= install

rt.rootdir := $(dir $(lastword $(MAKEFILE_LIST)))

ifndef V
clean::
	@echo "  CLEAN"
fclean:: clean
	@echo "  FCLEAN"
endif

include $(rt.rootdir)lib/toml/Makefile
include $(rt.rootdir)lib/obj/Makefile

rt.srcs :=
include src.mk

rt.objects := $(rt.srcs:.c=.o)
rt.objects := $(filter-out src/frontend/%, $(rt.objects))
rt.objects := $(addprefix $(rt.rootdir), $(rt.objects))

rt.sdl.o rt.wasm.o $(rt.objects): CPPFLAGS += -MMD -MP -I$(rt.rootdir)include
rt.sdl.o rt.wasm.o $(rt.objects): CPPFLAGS += -I$(libtoml.rootdir)include -I$(libobj.rootdir)include

rt.sdl.o: CPPFLAGS += $(shell $(PKG_CONFIG) --cflags sdl2 SDL2_image)
rt.sdl: LDLIBS += $(shell $(PKG_CONFIG) --libs sdl2 SDL2_image) -lm -lpthread

.PHONY: all
all: rt

vpath %.c $(rt.rootdir)src/frontend

rt.sdl: rt.sdl.o $(rt.objects) libtoml.a libobj.a

rt.wasm: CC = ${HOME}/.brew/opt/llvm/bin/clang
rt.wasm: CFLAGS += --target=wasm32 -ffunction-sections -fdata-sections -nostdlib -isystem $(realpath wasm/libc) -D__BSD_VISIBLE
rt.wasm: CPPFLAGS += -isystem $(realpath wasm/libc) -D__BSD_VISIBLE
rt.wasm: LDFLAGS = --target=wasm32 -ffunction-sections -fdata-sections -nostdlib -Wl,--no-entry -Wl,--allow-undefined -Wl,--export-dynamic -Wl,--import-memory -Wl,--stack-first
rt.wasm: rt.wasm.o $(filter-out $(rt.rootdir)src/render.o, $(rt.objects)) $(libtoml.objects) $(libobj.objects)

rt: rt.sdl
	$(INSTALL) -m 777 $< $@

.PHONY: clean
clean:: rt.objects += rt.sdl.o rt.wasm.o
clean::
	$(RM) $(rt.objects:.o=.{o,d,gcno,gcna})

.PHONY: fclean
fclean:: clean
	$(RM) -r rt rt.sdl rt.wasm

.PHONY: re
re: fclean all

ARFLAGS = rcs

-include $(wildcard $(rt.rootdir)*.d $(rt.rootdir)src/*.d $(rt.rootdir)src/*/*.d)

ifndef V
  $(eval COMPILE.c = @echo "  CC      $$(@F)"; $(value COMPILE.c))
  $(eval        AR = @echo "  AR      $$(@F)"; $(value AR))
  $(eval    LINK.o = @echo "  LD      $$(@F)"; $(value LINK.o))
  $(eval   INSTALL = @echo "  INSTALL $$(@F)"; $(value INSTALL))
  $(eval        RM = @$(value RM))
endif
