#include "SDL2/SDL.h"
#include "map.h"
#include "image.h"
#include "status.h"
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

void renderBackground(SDL_Renderer **render, NODO_IMG *img_header)
{
	SDL_Rect *src, *dst;

	SDL_SetRenderDrawColor(*render, 0, 0, 0, 255);	//Kolorea ezarri
	SDL_RenderClear(*render);	//Pantaila esandako kolorearekin garbitu

	if (img_header->img->dim.x != -1) dst = &img_header->img->dim;
	else dst = NULL;
	if (img_header->img->scroll.x != -1) src = &img_header->img->scroll;
	else src = NULL;

	SDL_RenderCopy(*render, img_header->img->texture, src, dst);

}

void renderObjects(SDL_Renderer **render, NODO_IMG *img_header, PATH fastestPath, PROCCESS current)
{
	pNODO_IMG aux;
	SDL_Rect aux2;

	aux = img_header;

	if (aux != NULL)
	{
		aux = aux->ptrNext;
	}
	if (current == ONROUTE) drawLines(*render, fastestPath);


	while (aux != NULL)
	{
		aux2.w = aux->img->dim.w;
		aux2.h = aux->img->dim.h;
		if (img_header->img->scroll.x < 0)
		{
			aux2.x = ((float)aux->img->dim.x / (float)IMG_WIDTH) * PANTAILA_ZABALERA;
			aux2.y = ((float)aux->img->dim.y / (float)IMG_HEIGHT) * PANTAILA_ALTUERA;
			aux2.x -= aux2.w/2;
			aux2.y -= aux2.h;
		}
		else
		{
			aux2.x = aux->img->dim.x - img_header->img->scroll.x;
			aux2.y = aux->img->dim.y - img_header->img->scroll.y;
//			aux2.w *= 2;
//			aux2.h *= 2;
		}
		SDL_RenderCopy(*render, aux->img->texture, NULL, &aux2);
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
	load_image(img_header, *render, "./media/gros5.bmp", -1, -1, 5002, 1926);
	load_map(map, "gros.dat", "gros_koord.dat");

	renderBackground(render, *img_header);
	refresh(*render);
}

void txapar(SDL_Window *window, SDL_Renderer *render)
{
	SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
}

void destroyMap(MAP **map)
{
	if (*map != NULL)
	{
		free(*map);
		*map = NULL;
	}
}

void destroyRender(pNODO_IMG *img_header, int content)
{
	pNODO_IMG aux, tmp;

	aux = *img_header;

	if (aux != NULL)
	{
		while (aux != NULL)
		{
			tmp = aux;
			aux = aux->ptrNext;
			if (content) free(tmp->img);
			free(tmp);
		}
		*img_header = NULL;
	}
}
