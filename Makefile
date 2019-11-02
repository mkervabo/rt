# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/12 13:29:47 by mkervabo          #+#    #+#              #
#    Updated: 2019/11/02 17:19:45 by dde-jesu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all
.SECONDARY:

PKG_CONFIG ?= pkg-config

V ?= @

rt.rootdir := $(dir $(lastword $(MAKEFILE_LIST)))

clean::
	@echo "  CLEAN"
fclean::
	@echo "  FCLEAN"

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

rt: LDLIBS += $(shell $(PKG_CONFIG) --libs sdl2 SDL2_image)

.PHONY: all
all: rt

vpath %.c $(rt.rootdir)src/frontend

rt.sdl: rt.sdl.o $(rt.objects) libtoml.a libobj.a

rt: rt.sdl
	@echo "  CP    $(<F) $(@F)"
	$(V)cp $< $@

.PHONY: clean
clean:: rt.objects += rt.sdl.o
clean::
	$(RM) $(rt.objects:.o=.{o,d,gcno,gcna})

.PHONY: fclean
fclean:: clean
	$(RM) -r rt rt.sdl

.PHNOY: re
re: fclean all

-include $(wildcard $(rt.rootdir)src/*.d $(rt.rootdir)src/*/*.d)

# just for style
define newline


endef

ARFLAGS = rcs

objects := rt.sdl.o $(rt.objects) $(libtoml.objects) $(libobj.objects)

$(objects): compile.c := $(COMPILE.c)
$(objects): COMPILE.c = @echo "  CC    $(@F)"$(newline)$(V)$(compile.c)

libtoml.a(%) libobj.a(%): ar := $(AR)
libtoml.a(%) libobj.a(%): AR = @echo "  AR    $(@F)($(<F))"$(newline)$(V)$(ar)

rt.sdl: link.o := $(LINK.o)
rt.sdl: LINK.o = @echo "  LN    $(@F)"$(newline)$(V)$(link.o)

clean fclean: rm := $(RM)
clean fclean: RM = $(V)$(rm)
