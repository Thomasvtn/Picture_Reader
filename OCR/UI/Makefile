GCC=gcc

CFLAGS=  -Wunused -Wall -fPIC -D REENTRANT
CFLAGS += -DGTK_DISABLE_DEPRECATED=1 -DGDK_DISABLE_DEPRECATED
CFLAGS += -DGDK_PIXBUF_DISABLE_DEPRECATED -DG_DISABLE_DEPRECATED
CFLAGS += -DGTK_MULTIHEAD_SAFE=1 -DGTK_MULTIDEVICE_SAFE=1
CFLAGS += `pkg-config --cflags gtk+-3.0`
CFLAGS += `pkg-config --cflags sdl` -MMD
CFLAGS +=  -Wextra -Werror -std=c99

LDLIBS= `pkg-config --libs sdl` -lSDL_image -lSDL_gfx

LDFLAGS= `pkg-config gtk+-3.0 --libs`
LDFLAGS += `pkg-config gmodule-2.0 --libs` -lm

EXEC=prog.exe
SRC=main.c ../segmentation/buildhisto.c ../segmentation/surface_operations.c \
	../segmentation/pixel_operations.c ../segmentation/sdl_func.c \
	../neural_network/layer.c ../neural_network/Network.c

all:main

main: 
	$(GCC) $(CFLAGS) $(SRC) -o $(EXEC) $(LDFLAGS) $(LDLIBS) 
clean:
	$(RM) $(EXEC)
	$(RM) *.o
	$(RM) *.d
