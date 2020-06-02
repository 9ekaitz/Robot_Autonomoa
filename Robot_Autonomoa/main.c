#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#include "map.h"
#include "image.h"
#include "basic.h"
#include "event.h"

//Ekaitz  v2
int main()
{

	STATUS app= {SDL_TRUE, SELECT};
    SDL_Window *window;                    // Declare a pointer
    SDL_Renderer *render;
    Uint32 refresh_rate = 0, check_rate = 0;
    NODO_IMG *img_header = NULL;
    MAP *map;
    ROUTE route = {{-1,-1},0};
    PATH fastestPath;

    windowandRender(&window, &render);

    launch(&render, &img_header, &map);

    while (app.run)
    {
    	if (SDL_TICKS_PASSED(SDL_GetTicks(), check_rate))
    	{
    		checkEvents(render, &app, &img_header, &route, map, &fastestPath);
    		check_rate = SDL_GetTicks() + 10;		//100 checks sgunduro
    	}
    	if (SDL_TICKS_PASSED(SDL_GetTicks(), refresh_rate))
    	{
    		renderBackground(&render, img_header);
    	    renderObjects(&render, img_header, fastestPath, app.current);
    	    refresh(render);
    	  	refresh_rate = SDL_GetTicks() + 50;		//20 fps
    	}
    }

    destroyMap(&map);
    destroyRender(&img_header, 1);

    txapar(window, render);
    SDL_Quit();
    return 0;
}
