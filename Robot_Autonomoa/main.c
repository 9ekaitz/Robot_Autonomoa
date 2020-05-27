#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "map.h"
#include "basic.h"
#include "event.h"

//Ekaitz  v2
int main(int argc, char* argv[]) {

	SDL_bool run = SDL_TRUE;
    SDL_Window *window;                    // Declare a pointer
    SDL_Renderer *render;
    Uint32 refresh_rate = 0, check_rate = 0;
    NODO_IMG *img_header = NULL;
    MAP *map;

    windowandRender(&window, &render);

    launch(&render, &img_header, &map);

    SDL_Delay(3000);


    while (run)
    {
    	if (SDL_TICKS_PASSED(SDL_GetTicks(), check_rate))
    	{
    		checkEvents(&run, &img_header);
    		check_rate = SDL_GetTicks() + 10;		//100 checks sgunduro
    	}
    	if (SDL_TICKS_PASSED(SDL_GetTicks(), refresh_rate))
    	{
    	    renderObjects(&render, img_header);
    	    refresh(render);
    	  	refresh_rate = SDL_GetTicks() + 50;		//20 fps
    	}
    }

//    destroy(&map, 0);
    destroy(&img_header, 1);

    txapar(window, render);
    SDL_Quit();
    return 0;
}


