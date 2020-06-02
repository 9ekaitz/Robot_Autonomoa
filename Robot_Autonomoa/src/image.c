#include "SDL2/SDL.h"
#include "map.h"
#include "image.h"

void load_image(pNODO_IMG *img_header, SDL_Renderer *render, char src[], int x, int y, int w, int h)
{

	IMG *image;

	load_imageData(&image, render, src, x, y, w, h);
	load_imageInsertBottom(img_header, image);

	// como ya he hecho la textura el surface no me hace falta y lo borro

}

int load_imageData(IMG **image, SDL_Renderer *render, char src[], int x, int y, int w, int h)
{
	SDL_Surface* surface;
	SDL_Texture* texture;

	IMG *tmp = (IMG *)malloc(sizeof(IMG));

	surface = SDL_LoadBMP(src);
	if (!surface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da argazkitik azalera sortu: %s\n", SDL_GetError());
		return -1;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	if (!texture)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da azaleratik textura sortu: %s\n", SDL_GetError());
		return -1;
	}

	SDL_FreeSurface(surface);

	tmp->texture = texture;

	rectBuilder(&tmp->dim, x, y, w, h); //sdl_rect estrukturari balioak emateko
	rectBuilder(&tmp->scroll, -1, -1, -1, -1); //sdl_rect estrukturari balioak emateko

	*image = tmp;

	return 0;
}

void load_imageInsertTop(pNODO_IMG *img_header, IMG *image)
{
	pNODO_IMG tmp = NULL;

	tmp = (NODO_IMG *)malloc(sizeof(NODO_IMG));

	tmp->img = image;
	tmp->ptrNext = *img_header;

	*img_header = tmp;
}

void load_imageInsertBottom(pNODO_IMG *img_header, IMG *image)
{
	pNODO_IMG aux, tmp;

	tmp = (NODO_IMG *)malloc(sizeof(NODO_IMG));

	tmp->img = image;
	tmp->ptrNext = NULL;

	aux = *img_header;

	if (aux == NULL) *img_header = tmp;
	else
	{
		while (aux->ptrNext != NULL)
		{
			aux = aux->ptrNext;
		}
		aux->ptrNext = tmp;
	}
}


void rectBuilder(SDL_Rect *rect, int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

void drawLines(SDL_Renderer *render, PATH fastestPath)
{
	SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);

	for (int i = 0; i < fastestPath.len-1; i++)
	{
		drawLine(render, fastestPath.vertex_koord[i], fastestPath.vertex_koord[i+1]);
	}
}

void drawLine(SDL_Renderer *render, PIXELKOORD src, PIXELKOORD dst)
{
	SDL_RenderDrawLine(render, src.x, src.y, dst.x, dst.y);
	SDL_RenderDrawLine(render, src.x, src.y+1, dst.x-1, dst.y);
	SDL_RenderDrawLine(render, src.x, src.y+2, dst.x-2, dst.y);
	SDL_RenderDrawLine(render, src.x, src.y+3, dst.x-3, dst.y);
	SDL_RenderDrawLine(render, src.x+1, src.y, dst.x, dst.y-1);
	SDL_RenderDrawLine(render, src.x+2, src.y, dst.x, dst.y-2);
	SDL_RenderDrawLine(render, src.x+3, src.y, dst.x, dst.y-3);
	SDL_RenderDrawLine(render, src.x, src.y, dst.x, dst.y);
	SDL_RenderDrawLine(render, src.x, src.y+1, dst.x-1, dst.y);
	SDL_RenderDrawLine(render, src.x, src.y+2, dst.x-2, dst.y);
	SDL_RenderDrawLine(render, src.x, src.y+3, dst.x-3, dst.y);
	SDL_RenderDrawLine(render, src.x+1, src.y, dst.x, dst.y-1);
	SDL_RenderDrawLine(render, src.x+2, src.y, dst.x, dst.y-2);
	SDL_RenderDrawLine(render, src.x+3, src.y, dst.x, dst.y-3);
	SDL_RenderDrawLine(render, src.x, src.y, dst.x, dst.y);
	SDL_RenderDrawLine(render, src.x, src.y+1, dst.x-1, dst.y);
	SDL_RenderDrawLine(render, src.x, src.y+2, dst.x-2, dst.y);
	SDL_RenderDrawLine(render, src.x, src.y+3, dst.x-3, dst.y);
	SDL_RenderDrawLine(render, src.x+1, src.y, dst.x, dst.y-1);
	SDL_RenderDrawLine(render, src.x+2, src.y, dst.x, dst.y-2);
	SDL_RenderDrawLine(render, src.x+3, src.y, dst.x, dst.y-3);
}
