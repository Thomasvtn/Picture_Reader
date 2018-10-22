#include <stdio.h>
#include "sdl_func.h"
#include "surface_operations.h"

int main()
{

	// Show grayscale and black to white
	init_sdl();

	SDL_Surface* picture = load_image("../ressources/grayscale_bw.png");

	grayscale_and_bw(picture);

	return 0;
}
