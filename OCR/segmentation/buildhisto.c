#include "buildhisto.h"

int* build_row_histo(SDL_Surface *picture)
{
	int width = picture->w;
	int height = picture->h;
	int black_pix_sum = 0;

	int* hor_histo = malloc(height*sizeof(int*));

	for (int row = 0; row < height; row++)
	{
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
	}

	return hor_histo;
}

int* build_col_histo(SDL_Surface *picture)
{

	int width = picture->w;
	int height = picture->h;
	int black_pix_sum = 0;

	int* col_histo = malloc(width*sizeof(int*));

	for (int col = 0; col < width; col++)
	{
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
	}

	return col_histo;
}
