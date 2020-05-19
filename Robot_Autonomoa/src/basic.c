#include "basic.h"


int LeihoaEtaRenderHasi(SDL_Window **window, SDL_Renderer **render)
{
	// SDL hasi
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin izan da SDL hasieratu: %s", SDL_GetError());
		return 1;
	}
	// Lehioa sortu eta ezaugarriak zehaztu

	*window = SDL_CreateWindow(
		"The Cave",                  			// Izenburua
		SDL_WINDOWPOS_CENTERED,           // Leihoa erdian jarri
		SDL_WINDOWPOS_CENTERED,           // Leihoa erdian jarri
		PANTAILA_ZABALERA,                // Sortzeko lehioaren zabalera
		PANTAILA_ALTUERA,                 // Sortzeko leihoaren altuera
		SDL_WINDOW_OPENGL                // Erabilitako teknologia grafikoa
	);

	if (*window == NULL) { 		// Leihoa sortu dela konprobatzen du

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin izan da leihoa sortu: %s\n", SDL_GetError());		//Errorea
		return 1;
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
