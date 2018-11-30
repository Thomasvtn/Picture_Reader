#ifndef BUILDHISTO_H
#define BUILDHISTO_H

#include <stdio.h>
//#include <SDL.h>
#include <SDL/SDL_image.h>
#include "pixel_operations.h"

int* build_row_histo(SDL_Surface *picture);
int* build_col_histo(SDL_Surface *picture);

#endif 
