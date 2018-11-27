#ifndef SURFACE_OPERATIONS_H
#define SURFACE_OPERATIONS_H

#include <stdio.h>
#include "buildhisto.h"
#include "sdl_func.h"
#include "pixel_operations.h"
#include "SDL/SDL_image.h"

//SDL_Surface* create_line_surface(SDL_Surface *picture, int begin, int end);
//SDL_Surface* create_char_surface(SDL_Surface *picture, int begin, int end);
SDL_Surface** select_line_surface(int* row_histo, SDL_Surface* picture);
SDL_Surface** select_char_surface(int* col_histo, SDL_Surface* picture);
SDL_Surface* grayscale(SDL_Surface *picture);
SDL_Surface* color_to_bw(SDL_Surface *picture);
void grayscale_and_bw(SDL_Surface* picture);
void all_in_one(SDL_Surface* picture);

#endif
