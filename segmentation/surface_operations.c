#include "surface_operations.h"

SDL_Surface* create_line_surface(SDL_Surface *picture, int begin, int end)
{
	//printf("create_line_surface\n");

	int width = picture->w;

	SDL_Surface* result = SDL_CreateRGBSurface(0, width, (end - begin)+1, 32, 0, 0, 0, 0);
	
	for (int row = begin; row <= end; row++)
	{
		for (int col = 0; col < width; col++)
		{
			Uint32 pixel = get_pixel(picture, col, row);

			Uint8 r, g, b;
			SDL_GetRGB(pixel, picture->format, &r, &g, &b);
			
			Uint32 result_pixel = get_pixel(result, col, row -begin);

			result_pixel = SDL_MapRGB(result->format, r, g, b);

			put_pixel(result, col, row -begin, result_pixel);
		}

	}

	return result;
}

SDL_Surface* create_char_surface(SDL_Surface *picture, int begin, int end)
{
	//printf("create_char_surface\n");

	int height = picture->h;

	SDL_Surface* result = SDL_CreateRGBSurface(0, (end - begin)+1, height, 32, 0, 0, 0, 0);
	
	for (int row = 0; row < height; row++)
	{
		for (int col = begin; col <= end; col++)
		{
			Uint32 pixel = get_pixel(picture, col, row);

			Uint8 r, g, b;
			SDL_GetRGB(pixel, picture->format, &r, &g, &b);

			Uint32 result_pixel = get_pixel(result, col -begin, row);

			result_pixel = SDL_MapRGB(result->format, r, g, b);

			put_pixel(result, col -begin, row, result_pixel);
		}

	}

	return result;
}


SDL_Surface** select_line_surface(int* row_histo, SDL_Surface* picture)
{
	//printf("select_line_surface\n");

	int height = picture->h;
	SDL_Surface** surface_list = malloc(height*sizeof(SDL_Surface*));
	int begin;
	int end;
	int nblines = 0;

	for (int row = 0; row < height; row++)
	{
		while(row < height && !row_histo[row])
			row++;

		begin = row;

		while(row < height && row_histo[row])
			row++;
		
		end = row -1;


		SDL_Surface* line_surface = create_line_surface(picture, begin, end);
		surface_list[nblines] = line_surface;
		nblines++;
	}

	return surface_list;
}

SDL_Surface** select_char_surface(int* col_histo, SDL_Surface* picture)
{
	//printf("select_char_surface\n");

	int width = picture->w;
	SDL_Surface** char_list = malloc(width*sizeof(SDL_Surface*));
	int begin;
	int end;
	int nbchars = 0;

	for (int col = 0; col < width; col++)
	{
		while(col < width && col_histo[col] == 0)
			col++;

		begin = col;

		while(col < width && col_histo[col+1] != 0)
		{
			if (col_histo[col] == 0)
				break;
			col++;
		}
		
		if (col_histo[col +1] != 0)
		{
			col += 1;

			while (col < width && col_histo[col] != 0)
				col++;
		}

		else if (col_histo[col +2] != 0)
		{
			col += 2;

			while (col < width && col_histo[col] != 0)
				col++;
		}

		else if (col_histo[col +3] != 0)
		{
			col += 3;

			while (col < width && col_histo[col] != 0)
				col++;
		}
		
		else if (col_histo[col +4] != 0)
		{
			col += 4;

			while (col < width && col_histo[col] != 0)
				col++;
		}

		end = col;

		//printf("%i  %i\n", begin, end);
		SDL_Surface* char_surface = create_char_surface(picture, begin, end);
		char_list[nbchars] = char_surface;
		nbchars++;
	}

	return char_list;
}

SDL_Surface* grayscale(SDL_Surface *picture)
{
	int width = picture->w;
	int height = picture->h;

	Uint8 r, g, b;
	Uint32 pixel;

	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			pixel = get_pixel(picture, i, j);
			SDL_GetRGB(pixel, picture->format, &r, &g, &b);

			Uint8 grey = (r + g + b) / 3;

			pixel = SDL_MapRGB(picture->format, grey, grey, grey);
			put_pixel(picture, i, j, pixel);
		}
	}

	return picture;

}

SDL_Surface* color_to_bw(SDL_Surface *picture)
{
	int width = picture->w;
	int height = picture->h;

	Uint8 r, g, b;
	Uint32 pixel;

	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			pixel = get_pixel(picture, i, j);

			SDL_GetRGB(pixel, picture->format, &r, &g, &b);

			Uint8 color = (r + g + b) / 3;

			if (color < 127)
				color = 0;
			else
				color = 255;

			pixel = SDL_MapRGB(picture->format, color, color, color);

			put_pixel(picture, i, j, pixel);
		}
	}

	return picture;
}

void grayscale_and_bw(SDL_Surface* picture)
{
	display_image(picture);
	wait_for_keypressed();
	
	SDL_Surface* grayscale_ = grayscale(picture);

	display_image(grayscale_);
	wait_for_keypressed();

	SDL_Surface* bw = color_to_bw(grayscale_);

	display_image(bw);
	wait_for_keypressed();

	SDL_FreeSurface(picture);
	SDL_FreeSurface(grayscale_);
	SDL_FreeSurface(bw);

	//printf("test\n");
}

void all_in_one(SDL_Surface* picture)
{
	//printf("all_in_one\n");
	
	display_image(picture);
	wait_for_keypressed();

	/* line separation */
	
	int* row_histo = build_row_histo(picture);

	SDL_Surface** line_array = select_line_surface(row_histo, picture);

	/*size_t lenght = sizeof(line_array);
	printf("%li\n", lenght);*/

	for (int i = 0; i < 2; i++)
	{
		//SDL_SaveBMP(line_array[i], ".");

		SDL_Surface* line = line_array[i];
		display_image(line);
		wait_for_keypressed();
	
		/* charactere separation */ 

		int* col_histo = build_col_histo(line);

		SDL_Surface** char_array = select_char_surface(col_histo, line);

		/*size_t lenght2 = sizeof(char_array);
		printf("%li", lenght2);*/

		for (int j = 0; j < 30; j++)
		{
			SDL_Surface* chara = char_array[j];
			display_image(chara);
			wait_for_keypressed();
			SDL_FreeSurface(chara);
		}

		SDL_FreeSurface(line);
	}
	SDL_FreeSurface(picture);
}
