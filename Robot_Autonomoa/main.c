#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#define SCREEN_W 1280
#define SCREEN_H 720
#define MAX_X_PHOTO 10210
#define MAX_Y_PHOTO 4993
#define BPP 50

//Gorka Scrolling
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_bool running = SDL_TRUE;
    SDL_Window *window;                    // Declare a pointer
    SDL_Surface* background;
    SDL_Rect camera;
    int x = 0, y = 0, speed = 5, FPS = 30;
    camera.x = 0;
    camera.y = 0;
    camera.w = SCREEN_W;
    camera.h = SCREEN_H;
    Uint32 start;

    background = SDL_LoadBMP("./media/background.bmp");

    //screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, BPP, SDL_SWSURFACE); //SDL_SWSURFACE: Create the video surface in system memory
    window = SDL_CreateWindow(
    		"OHM CARS SYSTEM",                  			// Izenburua
    		SDL_WINDOWPOS_CENTERED,           // Leihoa erdian jarri
    		SDL_WINDOWPOS_CENTERED,           // Leihoa erdian jarri
    		SCREEN_W,                // Sortzeko lehioaren zabalera
    		SCREEN_H,                 // Sortzeko leihoaren altuera
    		SDL_WINDOW_OPENGL                // Erabilitako teknologia grafikoa
    	);

    while (running)
    {
    	SDL_Event event;
    	while(SDL_PollEvent(&event))
    	{
    		switch(event.type)
			{
    		case SDL_QUIT:
    			running = SDL_FALSE;
    			break;
    		case SDL_KEYUP:
    			switch (event.key.keysym.sym)
    			{
    			case SDLK_RIGHT:
    				if(MAX_X_PHOTO-SCREEN_W >= camera.x)
    				{
    					x += speed;
    					camera.x += speed;
    				}
    				break;
    			case SDLK_LEFT:
    				if(camera.x >= 0)
    				{
    					x -= speed;
    					camera.x -= speed;
    				}
    				break;
    			case SDLK_UP:
    				if(MAX_Y_PHOTO-SCREEN_H >= camera.y)
    				{
    				    y += speed;
    				    camera.y += speed;
    				}
    				break;
    			case SDLK_DOWN:
    				if(camera.y >= 0)
    				{
    				   	y -= speed;
    					camera.y -= speed;
    				}
    				break;
    			}
			}
    	}
    	SDL_BlitSurface(background, &camera, window, NULL);
    	SDL_Flip(window);
    	if(1000/FPS>SDL_GetTicks()-start);
    	{
    		SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    	}
    }

    SDL_Quit();
    return 0;
}
