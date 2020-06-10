#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#include "map.h"
#include "graphic.h"
#include "basic.h"
#include "event.h"

//Gorka Defentsa
int main()
{

	STATUS app= {SDL_TRUE, SELECT_1}; //Aplikazioa funtzionatzen, ze procesu,
    SDL_Window *window;                    // Declare a pointer
    SDL_Renderer *render;
    TTF_Font *font;
    SDL_Color color = {0,0,0, 255};
    Uint32 refresh_rate = 0, check_rate = 0; //Para calcular relojes
    BACKGROUND *background; //textura, dim, SDL_Rect scroll
    NODO_OBJ *header = NULL, *toRender = NULL;
    MAP *map; //
    ROUTE route = {{-1,-1},0}; //Hasiera eta amaiera puntuak jasotzeko
    PATH fastestPath; //kostea, ibilbidea, puntu kop, puntuen pxkoordenatuak

    windowandRender(&window, &render, &font); //Lehioa, render eta letra mota hasieratu

    launch(&render, &background, &header, &map);	//Programa hasteko osagai basikoak kargatu (mapa eta bere datuak)

    while (app.run)
    {
    	if (SDL_TICKS_PASSED(SDL_GetTicks(), check_rate))
    	{
    		checkEvents(render, background, &app, &route, map);
    		refreshStatus(background, &app.current, render, &toRender, header, &route, map, &fastestPath, font, color);
    		check_rate = SDL_GetTicks() + 10;		//100 checks sgunduro
    	}
    	if (SDL_TICKS_PASSED(SDL_GetTicks(), refresh_rate))
    	{
    		renderBackground(&render, background);
    	    renderObjects(&render, background, toRender, fastestPath, &app.current);
    	    refresh(render);
    	  	refresh_rate = SDL_GetTicks() + 30;		//20 fps
    	}
    }

    destroyBackground(&background);
    destroyMap(&map);
    destroyObjects(&header, 1);

    txapar(window, render);
    SDL_Quit();
    return 0;
}
