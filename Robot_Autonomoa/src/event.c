#include "status.h"
#include "image.h"
#include "map.h"
#include "event.h"

void checkEvents(STATUS *app, pNODO_IMG *img_header, ROUTE *route, MAP *map)
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
				checkMouse((*img_header)->img, event.button, app, route, map);
				if (app->current == LA_RUTASE_ESTA_CALCULANDO)
				{
					dijkstra_dijknoestra();
					aparecerKotxe();
					app->current = ONROUTE;
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)		// SWITCH PARA LAS PULSACIONES DE TECLAS
				{
				case SDL_SCANCODE_UP:
					if ((*img_header)->img->scroll.y >= 15)
					{
						(*img_header)->img->scroll.y -= 15;
					}
					break;
				case SDL_SCANCODE_DOWN:
					if ((*img_header)->img->scroll.y + PANTAILA_ALTUERA <= (*img_header)->img->dim.h - 15)
					{
						(*img_header)->img->scroll.y += 15;
					}
					break;
				case SDL_SCANCODE_RIGHT:
					if ((*img_header)->img->scroll.x + PANTAILA_ZABALERA <= (*img_header)->img->dim.w-15)
					{
						(*img_header)->img->scroll.x += 15;
					}
					break;
				case SDL_SCANCODE_LEFT:
					if ((*img_header)->img->scroll.x >= 15)
					{
						(*img_header)->img->scroll.x -= 15;
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
						printf("prueba");
						rectBuilder(&(*img_header)->img->scroll, 0,0, PANTAILA_ZABALERA, PANTAILA_ALTUERA);
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
	mouse.x = x*6873/PANTAILA_ZABALERA;
	mouse.y = y*2912/PANTAILA_ALTUERA ;

	switch (event.button)
	{
		case SDL_BUTTON_LEFT:
			if (app->current == SELECT)
			{
				route->points[route->kop] = nearestPoint(map->koord, map->size, mouse);
				route->kop++;
				if (route->kop == 2)
				{
					app->current = LA_RUTASE_ESTA_CALCULANDO;
				}
			}
			break;

		case SDL_BUTTON_RIGHT:

			break;

		case SDL_BUTTON_MIDDLE:

			break;
	}
}
