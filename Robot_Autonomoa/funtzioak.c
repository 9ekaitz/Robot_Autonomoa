/*
 * funtzioak.c
 *
 *  Created on: 27 may. 2020
 *      Author: user
 */
#include "funtzioak.h"
#include <math.h>

void LerroaMarraztu(SDL_Renderer* renderer, int x1, int y1, int x2, int y2)
{
	 SDL_SetRenderDrawColor(renderer, 100, 31, 31, SDL_ALPHA_OPAQUE);
	 SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	 SDL_RenderPresent(renderer);
}
/*
float GeoDistantzia(float x1, float y1, float x2, float y2)
{
	return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}*/
