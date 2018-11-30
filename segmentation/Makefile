# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lSDL_gfx

all: main

main: sdl_func.o  buildhisto.o surface_operations.o pixel_operations.o main.o

main.o: sdl_func.h buildhisto.h surface_operations.h pixel_operations.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} main

# END
