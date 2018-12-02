#ifndef SURFACE_OPERATIONS_H
#define SURFACE_OPERATIONS_H

#include <stdio.h>
#include "buildhisto.h"
#include "pixel_operations.h"
#include "sdl_func.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "../neural_network/Network.h"
#include "../neural_network/layer.h"

void select_line_surface(SDL_Surface* picture, char finalresult[], Network net);
void select_char_surface(SDL_Surface* picture, int nblines, char finalresult[], Network net);
void color_bw(SDL_Surface* picture);
double* surface_binlist(SDL_Surface* picture);
double** list_binlist(char path[]); 

#endif
