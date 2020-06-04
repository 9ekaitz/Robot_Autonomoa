#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#include "map.h"
#include "graphic.h"
#include "basic.h"
#include "event.h"

//Ekaitz  v2
int main()
{

	STATUS app= {SDL_TRUE, SELECT};
    SDL_Window *window;                    // Declare a pointer
    SDL_Renderer *render;
    TTF_Font *font;
    SDL_Color color = {0,0,0, 255};
    Uint32 refresh_rate = 0, check_rate = 0;
    BACKGROUND *background;
    NODO_OBJ *header = NULL;
    MAP *map;
    ROUTE route = {{-1,-1},0};
    PATH fastestPath;

    windowandRender(&window, &render, &font); //Lehioa, render eta letra mota hasieratu

    launch(&render, &background, &map);	//Programa hasteko osagai basikoak kargatu (mapa eta bere datuak)

    while (app.run)
    {
    	if (SDL_TICKS_PASSED(SDL_GetTicks(), check_rate))
    	{
    		checkEvents(render, background, &app, &header, &route, map, &fastestPath, font, color);
    		check_rate = SDL_GetTicks() + 10;		//100 checks sgunduro
    	}
    	if (SDL_TICKS_PASSED(SDL_GetTicks(), refresh_rate))
    	{
    		renderBackground(&render, background);
    	    renderObjects(&render, background, header, fastestPath, app.current);
    	    refresh(render);
    	  	refresh_rate = SDL_GetTicks() + 50;		//20 fps
    	}
    }

    destroyBackground(&background);
    destroyMap(&map);
    destroyObjects(&header, 1);

    txapar(window, render);
    SDL_Quit();
    return 0;
}
