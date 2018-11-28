#ifndef SURFACE_OPERATIONS_H
#define SURFACE_OPERATIONS_H

#include <stdio.h>
#include "buildhisto.h"
#include "pixel_operations.h"
#include "sdl_func.h"
#include "SDL/SDL_image.h"

//SDL_Surface* create_line_surface(SDL_Surface *picture, int begin, int end);
//SDL_Surface* create_char_surface(SDL_Surface *picture, int begin, int end);
void select_line_surface(SDL_Surface* picture);
void select_char_surface(SDL_Surface* picture, int nblines);
void color_bw(SDL_Surface* picture);
void all_in_one(SDL_Surface* picture);

#endif
