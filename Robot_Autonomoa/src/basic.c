#include "SDL2/SDL.h"
#include "image.h"
#include "map.h"
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


void refresh(SDL_Renderer *render)	//dena marrasten du
{
	SDL_RenderPresent(render);
}

void renderObjects(SDL_Renderer **render, NODO_IMG *img_header)
{
	pNODO_IMG aux;
	SDL_Rect *src, *dst;

	SDL_SetRenderDrawColor(*render, 0, 0, 0, 255);	//Kolorea ezarri
	SDL_RenderClear(*render);	//Pantaila esandako kolorearekin garbitu

	aux = img_header;

	while (aux != NULL)
	{
		if (aux->img->dim.w != -1) dst = &aux->img->dim;
		else dst = NULL;
		if (aux->img->scroll.w != -1) src = &aux->img->scroll;
		else src = NULL;

		SDL_RenderCopy(*render, aux->img->texture, src, dst);
		aux = aux->ptrNext;
	}
	/*
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

void launch(SDL_Renderer **render, pNODO_IMG *img_header, MAP **map)
{

	load_image(img_header, *render, "./media/mapa.bmp", -1,-1,-1,-1);
	load_map(map, "gros");
	load_image(img_header, *render, "./media/punto.bmp", PANTAILA_ZABALERA/2,PANTAILA_ALTUERA/2,100,100);



	renderObjects(render, *img_header);
	refresh(*render);
}

void txapar(SDL_Window *window, SDL_Renderer *render)
{
	SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
}

void destroy(pNODO_IMG *img_header, int content)
{
	pNODO_IMG aux, tmp;

	aux = *img_header;

	if (aux != NULL)
	{
		while (aux != NULL)
		{
			tmp = *img_header;
			*img_header = (*img_header)->ptrNext;
			if (content) free(tmp->img);
			free(tmp);
		}
	}
}

