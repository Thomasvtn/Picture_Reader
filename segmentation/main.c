#include <stdio.h>
#include "sdl_func.h"
#include "surface_operations.h"

int main()
{
	// Segmentation
	init_sdl();

	SDL_Surface* image_surface = load_image("../ressources/text2_bw_28_1.jpg");

	all_in_one(image_surface);

	free(image_surface);
	
	return 0;
}
