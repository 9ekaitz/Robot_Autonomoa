#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "status.h"
#include "map.h"
#include "graphic.h"
#include "event.h"
#include "basic.h"

int windowandRender(SDL_Window **window, SDL_Renderer **render, TTF_Font **font)
{
	// SDL hasi
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Ezin izan da SDL hasieratu: %s", SDL_GetError());
		return -1;
	}

	if (TTF_Init() == -1)
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		return -1;
	}
	*font = TTF_OpenFont("./media/digital.TTF", 40);
	// Lehioa sortu eta ezaugarriak zehaztu

	*window = SDL_CreateWindow("Ohm Cars",    // Izenburua
			SDL_WINDOWPOS_CENTERED,           // Leihoa erdian jarri
			SDL_WINDOWPOS_CENTERED,           // Leihoa erdian jarri
			PANTAILA_ZABALERA,                // Sortzeko lehioaren zabalera
			PANTAILA_ALTUERA,                 // Sortzeko leihoaren altuera
			SDL_WINDOW_OPENGL                // Erabilitako teknologia grafikoa
			);

	if (*window == NULL)
	{ 		// Leihoa sortu dela konprobatzen du

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Ezin izan da leihoa sortu: %s\n", SDL_GetError());	//Errorea
		return -1;
	}

	/*
	 --------------IKONOA LEHIOAN------------------

	 SDL_Surface* ikonoa = SDL_LoadBMP(".\\media\\Ikonoa.bmp");
	 SDL_SetWindowIcon(leihoa, ikonoa);
	 SDL_FreeSurface(ikonoa);
	 */

	*render = SDL_CreateRenderer(*window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//Renderizatua hasi

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

	if (background->dim.x != -1)
		dst = &background->dim;
	else
		dst = NULL;
	if (background->scroll.x != -1)
		src = &background->scroll;
	else
		src = NULL;

	SDL_RenderCopy(*render, background->texture, src, dst);

}

void renderObjects(SDL_Renderer **render, BACKGROUND *background,
		NODO_OBJ *toRender, PATH fastestPath, PROCCESS *current)
{
	NODO_OBJ *aux;
	SDL_Rect aux2;

	aux = toRender;

	if (*current == ONROUTE)
		drawLines(background, *render, fastestPath);

	while (aux != NULL)
	{
		//Scroll-a dela eta argazkiak eskalatzeko eta leku egokian kokatzeko
		rectBuilder(&aux2, aux->obj->dim.x, aux->obj->dim.y, aux->obj->dim.w, aux->obj->dim.h);

		if (aux->obj->type != FONT)
		{
			if (background->scroll.x < 0)
			{
				aux2.x = ((float) aux->obj->dim.x / (float) IMG_WIDTH)
						* PANTAILA_ZABALERA;
				aux2.y = ((float) aux->obj->dim.y / (float) IMG_HEIGHT)
						* PANTAILA_ALTUERA;
			}
			else
			{
				aux2.x = aux->obj->dim.x - background->scroll.x;
				aux2.y = aux->obj->dim.y - background->scroll.y;
			}
		}
		//Argazkiaren 0,0 puntua "aldatu"
		switch (aux->obj->type)
		{
		case CAR:
			aux2.x -= aux2.w / 2;
			aux2.y -= aux2.h / 2;
			break;
		case FONT:
			break;
		default:
			aux2.x -= aux2.w / 2;
			aux2.y -= aux2.h;
			break;
		}

		if (aux->obj->type == CAR && *current == ONROUTE)
		{
			followTheLine(aux->obj, fastestPath, current, background);
		}
		//Render
		SDL_RenderCopy(*render, aux->obj->texture, NULL, &aux2);
		aux = aux->ptrNext;
	}

}

void launch(SDL_Renderer **render, pBACKGROUND *background, pNODO_OBJ *header,
		MAP **map)
{
	load_background(background, *render, "./media/Intro.bmp", 1280, 720);//mapa kargatu, src, w, h
	renderBackground(render, *background);	//pantaila renderizatu
	refresh(*render);
	SDL_Delay(2000);//Denbora hau mapak kargatzeko izango zen, baina fitxategi txikiak direnez delay jartzen diogu
	destroyBackground(background);
	load_background(background, *render, "./media/gros5.bmp", 5002, 1926);//mapa kargatu, src, w, h
	load_map(map, "gros.dat", "gros_koord.dat");//maparen datuak kargatu, distantzia matrizea eta koordenatuak

	load_image(header, *render, "./media/pointer.bmp", 0, 0, 30, 40, START);
	load_image(header, *render, "./media/meta.bmp", 0, 0, 37, 40, END);
	load_image(header, *render, "./media/punto.bmp", 0, 0, 50, 50, CAR);

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
		free((*map)->koord);
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
			if (content || tmp->obj->type == FONT)
				free(tmp->obj);
			free(tmp);
		}
		*header = NULL;
	}
}

void destroyBackground(pBACKGROUND *background)	//maparen argazkia memoriatik ezabatu
{
	if (*background != NULL)
	{
		free(*background);
		*background = NULL;
	}
}

void restart(BACKGROUND *background, pNODO_OBJ *toRender)
{
	background->scroll.x = -1;
	background->scroll.y = -1;
	destroyObjects(toRender, 0);
}
