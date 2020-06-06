#include <stdlib.h>
#include <math.h>
#include "status.h"
#include "map.h"
#include "graphic.h"
#include "basic.h"
#include "event.h"

void checkEvents(SDL_Renderer *render, BACKGROUND *background, STATUS *app,
		ROUTE *route, MAP *map)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			app->run = SDL_FALSE;
			break;
		case SDL_MOUSEBUTTONUP:
			checkMouse(event.button, app, route, map);
			break;
			//momentuz ez daukagu teklarik
		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode)
			// SWITCH PARA LAS PULSACIONES DE TECLAS
			{
			case SDL_SCANCODE_UP:
				if (background->scroll.y >= 15)
				{
					background->scroll.y -= 15;
				}
				break;
			case SDL_SCANCODE_DOWN:
				if (background->scroll.y + PANTAILA_ALTUERA
						<= background->dim.h - 15)
				{
					background->scroll.y += 15;
				}
				break;
			case SDL_SCANCODE_RIGHT:
				if (background->scroll.x + PANTAILA_ZABALERA
						<= background->dim.w - 15)
				{
					background->scroll.x += 15;
				}
				break;
			case SDL_SCANCODE_LEFT:
				if (background->scroll.x >= 15)
				{
					background->scroll.x -= 15;
				}
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_RETURN:
				rectBuilder(&background->scroll, 3000, 1000, PANTAILA_ZABALERA,
				PANTAILA_ALTUERA);
				break;
			case SDL_SCANCODE_ESCAPE:
				app->run = SDL_FALSE;
				break;
			default:
				break;
			}
			break;
		default:
			break;

		}
	}
}

void checkMouse(SDL_MouseButtonEvent event, STATUS *app, ROUTE *route, MAP *map)
{
	int x, y;
	PIXELKOORD mouse;
	SDL_GetMouseState(&x, &y);
	mouse.x = x * IMG_WIDTH / PANTAILA_ZABALERA;
	mouse.y = y * IMG_HEIGHT / PANTAILA_ALTUERA;

	switch (event.button)
	{
	case SDL_BUTTON_LEFT:
		if (app->current == SELECT_1)
		{
			route->points[0] = nearestPoint(map->koord, map->size, mouse);
			route->kop = 1;
		}
		if (app->current == SELECT_2)
		{
			route->points[1] = nearestPoint(map->koord, map->size, mouse);
			route->kop = 2;
		}
		break;
	case SDL_BUTTON_RIGHT:

		break;

	case SDL_BUTTON_MIDDLE:

		break;
	}
}

void moveCar(OBJECT *car, PIXELKOORD src, PIXELKOORD dst)
{
	int *x = &car->dim.x;
	int *y = &car->dim.y;
	float angle;

	angle = atan2f((dst.y - *y), (dst.x - *x));

	*x = *x + SPEED*cosf(angle);
	*y = *y + SPEED*sinf(angle);
}

int checkNode(OBJECT *car, PIXELKOORD src, PIXELKOORD dst)
{

	int x = car->dim.x;	//Puntuarena

	/*
	 * Xabi (Valencia) perdon por este pecado que voy a cometer con los return, pero queda mas limpito
	 */

	if (src.x > dst.x)
	{
		if (x <= dst.x)
		{
			return 1;
		}
	}
	else
	{
		if (x >= dst.x)
		{
			return 1;
		}
	}
	return 0;
}

void followTheLine(OBJECT *car, PATH fastestPath, PROCCESS *current)
{
	static int x = 0;
	int skip;

	//si la X,Y de la imagen pasa la X,Y del siguiente nodo entra.

	do
	{
		skip = checkNode(car, fastestPath.vertex_koord[x],
				fastestPath.vertex_koord[x + 1]);
		if (skip)
		{
			x += 1;
		}
	} while (skip);

	moveCar(car, fastestPath.vertex_koord[x], fastestPath.vertex_koord[x + 1]);
	if (x >= fastestPath.len - 1)
	{
		x = 0;
		*current = FINISHED;
	}
}

void refreshStatus(BACKGROUND *background, PROCCESS *current,
		SDL_Renderer *render, pNODO_OBJ *toRender, NODO_OBJ *header,
		ROUTE *route, MAP *map, PATH *fastestPath, TTF_Font *font,
		SDL_Color color)
{
	PIXELKOORD endPoint, startPoint;
	NODO_OBJ *aux = header;

	switch (*current)
	{
	case SELECT_1:
		if (route->kop == 1)
		{
			startPoint = coordToPixel(map->koord[route->points[0]]);
			while (aux != NULL && aux->obj->type != START)
			{
				aux = aux->ptrNext;
			}
			load_objectInsertBottom(toRender, aux->obj);
			aux->obj->dim.x = startPoint.x;
			aux->obj->dim.y = startPoint.y;
			//load;
			*current = SELECT_2;
		}
		break;
	case SELECT_2:
		if (route->kop == 2)
		{
			startPoint = coordToPixel(map->koord[route->points[0]]);
			endPoint = coordToPixel(map->koord[route->points[1]]);
			while (aux != NULL && aux->obj->type != END)
			{
				aux = aux->ptrNext;
			}
			load_objectInsertBottom(toRender, aux->obj);
			aux->obj->dim.x = endPoint.x;
			aux->obj->dim.y = endPoint.y;
			aux = header;
			while (aux != NULL && aux->obj->type != CAR)
			{
				aux = aux->ptrNext;
			}
			load_objectInsertBottom(toRender, aux->obj);
			aux->obj->dim.x = startPoint.x;
			aux->obj->dim.y = startPoint.y;

			//load
			route->kop = 0;
			*fastestPath = A_star(*map, route->points[0], route->points[1]);
			fillPathKoord(map->koord, fastestPath);
			load_font(toRender, render, fastestPath->cost, font, color);
			//aparecerKotxe();
			*current = ONROUTE;
		}
		break;
	case ONROUTE:
		break;
	case FINISHED:
		restart(background, toRender);
		*current = SELECT_1;
		break;
	default:
		break;
	}
}
