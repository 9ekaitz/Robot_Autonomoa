#include "SDL2/SDL.h"
#include <stdio.h>
#include <limits.h> //INT_MAX
#include <float.h> //FLT_MAX
#include "funtzioak.h"
#define DEFINITUGABEA -1

//Gorka
int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        1280,                               // width, in pixels
        720,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    //////////////////////////////////////////////////////////////////////
    //https://es.scribd.com/doc/44021747/Algoritmo-Dijkstra-en-c
    //////////////////////////////////////////////////////////////////////
    int M, A, B;
    char str[128];
    //matrizeak hasieratu

    fgets(str, 128, stdin);
    sscanf(str, "%d", &M);

    for (int i = 0; i < N; ++i)
    {
		aurrekoa[i] = DEFINITUGABEA;
		bisitatua[i] = FALSE;
		minimo[i] = INT_MAX;
		for (int j = 0; j < M; ++j)
		{
			bidea[i][j] = FLT_MAX;
		}
	}

    //Distantziak neurtu i

    //////////////////////////////////////////////////////////////////////

    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
