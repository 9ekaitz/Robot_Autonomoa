#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include "funtzioak.h"

//Gorka Line creating v1.2

int main(int argc, char* argv[])
{
	int x1 = 0, y1 = 0, x2, y2; //X1 e Y1 son las coordenadas en las que se encuentra el coche antes de iniciar el recorrido
	char str[128];

	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
	        SDL_Window* window = NULL;
	        SDL_Renderer* renderer = NULL;

	        if (SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer) == 0)
	        {
	            SDL_bool done = SDL_FALSE;

	            while (!done) {
	                SDL_Event event;

	                // DIBUJAR CON COORDENADAS
	                printf("\nx1, y1:");
	                fgets(str, 128, stdin);
	                sscanf(str, "%d %d", &x2, &y2);
	                LerroaMarraztu(renderer, x1, y1, x2, y2);
	                x1 = x2;
	                y1 = y2;
	                /*
	                printf("\nx1, y1, x2, y2:");
	                fgets(str, 128, stdin);
	                sscanf(str, "%d %d %d %d", &x1, &y1, &x2, &y2);

	                printf("\nDistantzia: %f", GeoDistantzia(x1, x2, y1, y2));*/

	                if(SDL_PollEvent(&event)) {
	                    if (event.type == SDL_QUIT) {
	                        done = SDL_TRUE;
	                    }
	                }
	            }
	        }

	        if (renderer) {
	            SDL_DestroyRenderer(renderer);
	        }
	        if (window) {
	            SDL_DestroyWindow(window);
	        }
	    }
	    SDL_Quit();
	    return 0;
}
