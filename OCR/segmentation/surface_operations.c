#include "surface_operations.h"

void select_line_surface(SDL_Surface* picture, char finalresult[], Network net)
{
	color_bw(picture);

	int* row_histo = build_row_histo(picture);
	int height = picture->h;
	int width = picture->w;

	char path[] = "lines_save/line";
	char ext[] = ".bmp";
	char final_path[200];
	char countstr[200];
	int nblines = 0;

	int begin;
	int end = 0;

	SDL_Rect srcrect;

	for (int row = 0; row < height; row++)
	{

		while(row < height && !row_histo[row])
			row++;

		begin = row;

		while(row < height && row_histo[row])
			row++;

		end = row -1;

		if (end - begin < 5)
			continue;

		srcrect.x = 0;
		srcrect.y = begin;
		srcrect.w = width;
		srcrect.h = (end - begin) +1;
		SDL_Surface* line_surface = SDL_CreateRGBSurface(0, width, (end - begin) + 1, 32, 255, 255, 255, 0);
		SDL_BlitSurface(picture, &srcrect, line_surface, NULL);
	
		sprintf(countstr,"%d",nblines);
		strcpy(final_path, path);
		strcat(final_path, countstr);
		strcat(final_path, ext);
		SDL_SaveBMP(line_surface, final_path);
		nblines++;

		select_char_surface(line_surface, nblines, finalresult, net);

		strcat(finalresult, "\n");
	}
}

void select_char_surface(SDL_Surface* picture, int nblines, char finalresult[], Network net)
{
	int* col_histo = build_col_histo(picture);
	int width = picture->w;
	int heigth = picture->h;
	
	char path[] = "char_save/line";
	char charnb[] = "_char";
	char ext[] = ".bmp";
	char final_path[200];
	char countlines[200];
	char countchar[200];
	int nbchars = 0;

	int begin;
	int end = 0;
	SDL_Rect srcrect;

	for (int col = 0; col < width; col++)
	{
		SDL_Surface* char_surface;

		while(col < width && col_histo[col] == 0)
			col++;

		begin = col;

		if (col - end > 10)
		{
			char_surface = SDL_CreateRGBSurface(0, 28, 28, 32, 0, 0, 0, 0);

			sprintf(countlines, "%d", nblines);
			strcpy(final_path, path);
			strcat(final_path, countlines);
			strcat(final_path, charnb);
			sprintf(countchar, "%d", nbchars);
			strcat(final_path, countchar);
			strcat(final_path, ext);
			printf("%s\n", final_path);
			SDL_SaveBMP(char_surface, final_path);	
			nbchars++;

			strcat(finalresult, " ");
		}

		while(col < width && col_histo[col+1] != 0)
			col++;

		end = col;

		if (end - begin < 5)
			continue;

		srcrect.x = begin;
		srcrect.y = 0;
		srcrect.w = (end - begin);
		srcrect.h = heigth;
		char_surface = SDL_CreateRGBSurface(0, (end - begin)+1, heigth, 32, 255, 255, 255, 0);
		SDL_BlitSurface(picture, &srcrect, char_surface, NULL);
		SDL_Surface* char_surface_resized;

		double width = char_surface->w;
		double heigth = char_surface->h;

		double zoomx = 16 / width;
		double zoomy = 16 / heigth;

		char_surface_resized = zoomSurface(char_surface, zoomx, zoomy, 1);

		double *int_ = surface_binlist(char_surface_resized);
			
		sprintf(countlines, "%d", nblines);
		strcpy(final_path, path);
		strcat(final_path, countlines);
		strcat(final_path, charnb);
		sprintf(countchar, "%d", nbchars);
		strcat(final_path, countchar);
		strcat(final_path, ext);
		SDL_SaveBMP(char_surface_resized, final_path);
		nbchars++;

		double *out = calloc(net.input_dim, sizeof(double));

		char the_one = (char)predict(&net, int_, out);

		char *tmp = malloc(2*sizeof(char));
		tmp[0] = the_one;

		strcat(finalresult, tmp);

		free(tmp);
	}
}

void color_bw(SDL_Surface* picture)
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
}

double* surface_binlist(SDL_Surface* picture)
{
	int width = picture->w;
	int height = picture->h;
	double* result = malloc((width*height)*sizeof(double));
	Uint8 r, g ,b;
	Uint32 pixel;

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			pixel = get_pixel(picture, row, col);
			SDL_GetRGB(pixel, picture->format, &r, &g, &b);

			if(r == 0)
				result[row * width + col] = 1; //noir
			else
				result[row * width + col] = 0; //blanc
		}
	}
	return result;
}

double** list_binlist(char path[]) //../ressources/database/1/
{
	double **inputlist = malloc(58 * sizeof(double));

	init_sdl();

	for(int i = 97; i < 55+97; i++)
	{
		char final_path[70];
		char ibis[5];
		char ext[] = ".bmp";

		strcpy(final_path, path);

		sprintf(ibis, "%d", (i-97));

		strcat(final_path, ibis);

		strcat(final_path, ext);

		SDL_Surface* image_surface = load_image(final_path);

		printf("%s\n", final_path);

		double *image1 = surface_binlist(image_surface);

		for (size_t i = 0; i < 256; i++)
			printf("%f", *(image1 +i));
		printf("\n");

		inputlist[i-97] = image1;
	}

	return inputlist;
}
