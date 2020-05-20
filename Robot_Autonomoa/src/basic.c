#include "basic.h"


int windowandRender(SDL_Window **window, SDL_Renderer **render)
{
	// SDL hasi
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin izan da SDL hasieratu: %s", SDL_GetError());
		return -1;
	}
	// Lehioa sortu eta ezaugarriak zehaztu

	*window = SDL_CreateWindow(
		"OSM",                  			// Izenburua
		SDL_WINDOWPOS_CENTERED,           // Leihoa erdian jarri
		SDL_WINDOWPOS_CENTERED,           // Leihoa erdian jarri
		PANTAILA_ZABALERA,                // Sortzeko lehioaren zabalera
		PANTAILA_ALTUERA,                 // Sortzeko leihoaren altuera
		SDL_WINDOW_OPENGL                // Erabilitako teknologia grafikoa
	);

	if (*window == NULL) { 		// Leihoa sortu dela konprobatzen du

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin izan da leihoa sortu: %s\n", SDL_GetError());		//Errorea
		return -1;
	}
 /*
    --------------IKONOA LEHIOAN------------------

	SDL_Surface* ikonoa = SDL_LoadBMP(".\\media\\Ikonoa.bmp");
	SDL_SetWindowIcon(leihoa, ikonoa);
	SDL_FreeSurface(ikonoa);
*/

	*render = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);		//Renderizatua hasi

	return 0;
}

void close(SDL_Window **window, SDL_Renderer **render)
{
	SDL_DestroyWindow(*window);
	SDL_DestroyRenderer(*render);
}

void refresh(SDL_Renderer **render)	//dena marrasten du
{
	SDL_RenderPresent(*render);
}

void renderObjects(SDL_Renderer **render)
{
	SDL_SetRenderDrawColor(*render, 0, 0, 0, 255);	//Kolorea ezarri
	SDL_RenderClear(*render);	//Pantaila esandako kolorearekin garbitu

//	SDL_RenderCopy(render, Irudiak[i].textura, NULL, NULL);
	/**
	 *  \brief Copy a portion of the texture to the current rendering target.
	 *
	 *  \param renderer The renderer which should copy parts of a texture.
	 *  \param texture The source texture.
	 *  \param srcrect   A pointer to the source rectangle, or NULL for the entire
	 *                   texture.
	 *  \param dstrect   A pointer to the destination rectangle, or NULL for the
	 *                   entire rendering target.
	 *
	 *  \return 0 on success, or -1 on error
	 */

}

//void launch(SDL_Renderer **render, )
//{
//
//}
//

void load_image(pNODO_IMG *img_header, SDL_Renderer *render, char src[], int x, int y, int w, int h)
{

	IMG *image;

	load_imageData(&image, render, src, x, y, w, h);
	load_imageInsert(img_header, image);

	// como ya he hecho la textura el surface no me hace falta y lo borro

}

int load_imageData(IMG **image, SDL_Renderer *render, char src[], int x, int y, int w, int h)
{
	SDL_Surface* surface;
	SDL_Texture* texture;

	IMG *tmp = (IMG *)malloc(sizeof(IMG));

	surface = SDL_LoadBMP(src);
	if (!surface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da argazkitik azalera sortu: %s\n", SDL_GetError());
		return -1;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	if (!texture)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da azaleratik textura sortu: %s\n", SDL_GetError());
		return -1;
	}

	SDL_FreeSurface(surface);

	tmp->texture = texture;
	rectBuilder(&(*image)->dim, x, y, w, h); //sdl_rect estrukturari balioak emateko

	*image = tmp;

	return 0;
}

void rectBuilder(SDL_Rect *rect, int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}
