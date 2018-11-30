#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "sdl_func.h"
#include "surface_operations.h"

int main(int argc, char **argv)
{
	// Segmentation

	if (argc > 2)
		errx(1, "Error");

	init_sdl();

	SDL_Surface* image_surface = load_image(argv[1]);

	all_in_one(image_surface);

	free(image_surface);
	
	return 0;
}
