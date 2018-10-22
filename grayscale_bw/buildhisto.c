#include "buildhisto.h"

int* build_row_histo(SDL_Surface *picture)
{
	printf("build_row_histo\n");

	int width = picture->w;
	int height = picture->h;
	int black_pix_sum = 0;

	int* hor_histo = malloc(height*sizeof(int*));

	for (int row = 0; row < height; row++)
	{
		SDL_LockSurface(picture);

		for (int col = 0; col < width; col++)
		{
			Uint32 pixel = get_pixel(picture, col, row);

			Uint8 r, g, b;
			SDL_GetRGB(pixel, picture->format, &r, &g, &b);

			if (r == 0 && g == 0 && b == 0)
				black_pix_sum += 1;
		}

		//if (black_pix_sum <= 3)
		//	black_pix_sum = 0;
		
		hor_histo[row] = black_pix_sum;

		black_pix_sum = 0;

		SDL_UnlockSurface(picture);
	}

	return hor_histo;
}

int* build_col_histo(SDL_Surface *picture)
{
	printf("build_col_histo\n");

	int width = picture->w;
	int height = picture->h;
	int black_pix_sum = 0;

	int* col_histo = malloc(height*sizeof(int*));

	for (int col = 0; col < width; col++)
	{
		SDL_LockSurface(picture);

		for (int row = 0; row < height; row++)
		{
			Uint32 pixel = get_pixel(picture, col, row);

			Uint8 r, g, b;
			SDL_GetRGB(pixel, picture->format, &r, &g, &b);

			if (r == 0 && g == 0 && b == 0)
			{
				black_pix_sum += 1;
			}
		}

		col_histo[col] = black_pix_sum;
		//printf("%i\n", black_pix_sum);
		
		black_pix_sum = 0;

		SDL_UnlockSurface(picture);
	}

	return col_histo;
}
