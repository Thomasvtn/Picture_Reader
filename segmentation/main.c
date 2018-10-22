#include <stdio.h>
#include "sdl_func.h"
#include "surface_operations.h"

int main()
{
	// Segmentation
	init_sdl();

	SDL_Surface* image_surface = load_image("../ressources/test_segmentation.jpg");

	all_in_one(image_surface);
	
	return 0;
}
