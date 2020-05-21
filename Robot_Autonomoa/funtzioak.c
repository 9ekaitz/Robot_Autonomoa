/*
 * funtzioak.c
 *
 *  Created on: 20 may. 2020
 *      Author: gorkalertxundi
 */
#include "SDL2/SDL.h"
#include <stdio.h>

SDL_Renderer* render;

void ImgKargatu(char src[], int zabalera, int altuera, int x, int y)
{
	SDL_Surface* surface;
	SDL_Texture* texture;

	surface = SDL_LoadBMP(src);
	if (!surface) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da argazkitik azalera sortu: %s\n", SDL_GetError());
		return;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	if (!texture) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da azaleratik textura sortu: %s\n", SDL_GetError());
		return;
	}
	SDL_FreeSurface(surface);

}
