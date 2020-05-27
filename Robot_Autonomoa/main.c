#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "basic.h"

//Koordenatuak irakurri
int main(int argc, char* argv[]) {

	SDL_bool run = SDL_TRUE;
    SDL_Window *window;                    // Declare a pointer
    SDL_Renderer *render;
    Uint32 refresh_rate = 0;
    NODO_IMG *img_header = NULL;

    windowandRender(&window, &render);

    launch(&render, &img_header);

    SDL_Delay(3000);


    while (run)
    {
    	if (SDL_TICKS_PASSED(SDL_GetTicks(), refresh_rate))
    	{
    		renderObjects(&render, img_header);
    		refresh(render);
    		refresh_rate = SDL_GetTicks() + 50;		//20 fps
    	}
    }

    txapar(window, render);
    SDL_Quit();
    return 0;
}
