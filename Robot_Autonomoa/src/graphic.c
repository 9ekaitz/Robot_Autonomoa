#include "SDL2/SDL.h"
#include <strings.h>
#include "map.h"
#include "graphic.h"


void load_background(pBACKGROUND *background, SDL_Renderer *render, char src[], int w, int h)
{
	SDL_Surface* surface;
	SDL_Texture* texture;

	BACKGROUND *tmp = (BACKGROUND *)malloc(sizeof(BACKGROUND));

	surface = SDL_LoadBMP(src);
	if (!surface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da argazkitik azalera sortu: %s\n", SDL_GetError());
		return;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	if (!texture)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da azaleratik textura sortu: %s\n", SDL_GetError());
			return;
	}

	SDL_FreeSurface(surface);

	tmp->texture = texture;

	rectBuilder(&tmp->dim, -1, -1, w, h); //sdl_rect estrukturari balioak emateko
	rectBuilder(&tmp->scroll, -1, -1, -1, -1); //sdl_rect estrukturari balioak emateko

	*background = tmp;
}

void load_image(pNODO_OBJ *header, SDL_Renderer *render, char src[], int x, int y, int w, int h)
{

	OBJECT *image;

	load_imageData(&image, render, src, x, y, w, h);
	load_objectInsertBottom(header, image);

	// como ya he hecho la textura el surface no me hace falta y lo borro

}

void load_imageData(OBJECT **object, SDL_Renderer *render, char src[], int x, int y, int w, int h)
{
	SDL_Surface* surface;
	SDL_Texture* texture;

	OBJECT *tmp = (OBJECT *)malloc(sizeof(OBJECT));

	surface = SDL_LoadBMP(src);
	if (!surface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da argazkitik azalera sortu: %s\n", SDL_GetError());
		return;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	if (!texture)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da azaleratik textura sortu: %s\n", SDL_GetError());
		return;
	}

	SDL_FreeSurface(surface);

	tmp->texture = texture;

	rectBuilder(&tmp->dim, x, y, w, h); //sdl_rect estrukturari balioak emateko

	*object = tmp;
}

void load_objectInsertTop(pNODO_OBJ *header, OBJECT *object)
{
	pNODO_OBJ tmp = NULL;

	tmp = (NODO_OBJ *)malloc(sizeof(NODO_OBJ));

	tmp->obj = object;
	tmp->ptrNext = *header;

	*header = tmp;
}

void load_objectInsertBottom(pNODO_OBJ *header, OBJECT *object)
{
	pNODO_OBJ aux, tmp;

	tmp = (NODO_OBJ *)malloc(sizeof(NODO_OBJ));

	tmp->obj = object;
	tmp->ptrNext = NULL;

	aux = *header;

	if (aux == NULL) *header = tmp;
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

void drawLines(BACKGROUND *background, SDL_Renderer *render, PATH fastestPath)
{
	SDL_SetRenderDrawColor(render, 255, 80, 80, SDL_ALPHA_OPAQUE);

	for (int i = 0; i < fastestPath.len-1; i++)
	{
		drawLine(background, render, fastestPath.vertex_koord[i], fastestPath.vertex_koord[i+1]);
	}
}

void drawLine(BACKGROUND *background, SDL_Renderer *render, PIXELKOORD src, PIXELKOORD dst)
{
	if (background->scroll.x < 0)
	{
		src.x = ((float)src.x / (float)IMG_WIDTH) * PANTAILA_ZABALERA;
		src.y = ((float)src.y / (float)IMG_HEIGHT) * PANTAILA_ALTUERA;
		dst.x = ((float)dst.x / (float)IMG_WIDTH) * PANTAILA_ZABALERA;
		dst.y = ((float)dst.y / (float)IMG_HEIGHT) * PANTAILA_ALTUERA;
	}
	else
	{
		src.x -= background->scroll.x;
		src.y -= background->scroll.y;
		dst.x -= background->scroll.x;
		dst.y -= background->scroll.y;
	}

	SDL_RenderDrawLine(render, src.x, src.y, dst.x, dst.y);
	SDL_RenderDrawLine(render, src.x, src.y+1, dst.x-1, dst.y);
	SDL_RenderDrawLine(render, src.x+1, src.y, dst.x, dst.y-1);
}

void load_fontData(OBJECT **object, SDL_Renderer *render, TTF_Font *font, SDL_Color color, char text[], int x, int y)
{
	SDL_Surface* surface;
	SDL_Texture* texture;

	OBJECT *tmp = (OBJECT *)malloc(sizeof(OBJECT));

	surface = TTF_RenderText_Solid(font, text, color);
	if (!surface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da argazkitik azalera sortu: %s\n", SDL_GetError());
		return;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	if (!texture)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da azaleratik textura sortu: %s\n", SDL_GetError());
		return;
	}

	SDL_FreeSurface(surface);

	tmp->texture = texture;

	SDL_QueryTexture(texture, NULL, NULL, &tmp->dim.w, &tmp->dim.h); //sdl_rect estrukturari balioak emateko
	tmp->dim.x = x;
	tmp->dim.y = y;


	*object = tmp;
}

void load_font(pNODO_OBJ *header, SDL_Renderer *render, float cost, TTF_Font *font, SDL_Color color)
{
	OBJECT *object;
	char text[128];

	sprintf(text, "%.2f", cost);
	strcat(text, " m");

	load_fontData(&object, render, font, color, text, 1000, 500);
	load_objectInsertBottom(header, object);
}
