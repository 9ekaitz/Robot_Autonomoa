#include "SDL2/SDL.h"
#include "map.h"
#include "graphic.h"
#include "status.h"
#include "basic.h"



int windowandRender(SDL_Window **window, SDL_Renderer **render, TTF_Font **font)
{
	// SDL hasi
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin izan da SDL hasieratu: %s", SDL_GetError());
		return -1;
	}

	if(TTF_Init()==-1) {
	    printf("TTF_Init: %s\n", TTF_GetError());
	    return -1;
	}
	*font = TTF_OpenFont("./media/digital.TTF", 100);
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

void renderBackground(SDL_Renderer **render, BACKGROUND *background)
{
	SDL_Rect *src, *dst;

	SDL_SetRenderDrawColor(*render, 0, 0, 0, 255);	//Kolorea ezarri
	SDL_RenderClear(*render);	//Pantaila esandako kolorearekin garbitu

	if (background->dim.x != -1) dst = &background->dim;
	else dst = NULL;
	if (background->scroll.x != -1) src = &background->scroll;
	else src = NULL;

	SDL_RenderCopy(*render, background->texture, src, dst);

}

void renderObjects(SDL_Renderer **render, BACKGROUND *background, NODO_OBJ *header, PATH fastestPath, PROCCESS current)
{
	NODO_OBJ *aux;
	SDL_Rect aux2;
	int i = 0;

	aux = header;

	if (current == ONROUTE)
	drawLines(background, *render, fastestPath);

	while (aux != NULL)
	{
		//Scroll-a dela eta argazkiak eskalatzeko eta leku egokian kokatzeko
		aux2.w = aux->obj->dim.w;
		aux2.h = aux->obj->dim.h;
		if (background->scroll.x < 0)
		{
			aux2.x = ((float)aux->obj->dim.x / (float)IMG_WIDTH) * PANTAILA_ZABALERA;
			aux2.y = ((float)aux->obj->dim.y / (float)IMG_HEIGHT) * PANTAILA_ALTUERA;
		}
		else
		{
			aux2.x = aux->obj->dim.x - background->scroll.x;
			aux2.y = aux->obj->dim.y - background->scroll.y;
		}
		//Argazkiaren 0,0 puntua "aldatu"
		aux2.x -= aux2.w/2;
		aux2.y -= aux2.h;
		if (i == 2)
		{
			moveCar(fastestPath, aux->obj);
		}
		//Render
		SDL_RenderCopy(*render, aux->obj->texture, NULL, &aux2);
		aux = aux->ptrNext;
		i++;
	}

}

void launch(SDL_Renderer **render, pBACKGROUND *background, MAP **map)
{
	load_background(background, *render, "./media/gros5.bmp", 5002, 1926);	//mapa kargatu, src, w, h
	load_map(map, "gros.dat", "gros_koord.dat");	//maparen datuak kargatu, distantzia matrizea eta koordenatuak

	renderBackground(render, *background);	//pantaila renderizatu
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

void destroyObjects(pNODO_OBJ *header, int content)
{
	pNODO_OBJ aux, tmp;

	aux = *header;

	if (aux != NULL)
	{
		while (aux != NULL)
		{
			tmp = aux;
			aux = aux->ptrNext;
			if (content) free(tmp->obj);
			free(tmp);
		}
		*header = NULL;
	}
}

void destroyBackground(pBACKGROUND *background)	 //maparen argazkia memoriatik ezabatu
{
	if (*background != NULL)
	{
		free(*background);
		*background = NULL;
	}
}
