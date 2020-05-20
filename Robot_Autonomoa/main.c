#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include "basic.h"

//Ekaitz
int main(int argc, char* argv[]) {

	SDL_bool run = SDL_TRUE;
    SDL_Window *window;                    // Declare a pointer
    SDL_Renderer *render;
    Uint32 refresh_rate = 0;
    NODO_IMG *img_header;

    if (windowandRender( &window, &render) != -1)
    {
    	if (window == NULL)
    	{
    		SDL_DestroyWindow(window);	// Close and destroy the window
    	}

    }

//    launch(&render, &img_header);

    while (run)
    {
    	if (SDL_TICKS_PASSED(SDL_GetTicks(), refresh_rate))
    	{
    		renderObjects();
    		refresh(&render);
    		refresh_rate = SDL_GetTicks() + 50;		//20 fps
    	}
    }

    close(&window, &render);

    SDL_Quit();
    return 0;
}
