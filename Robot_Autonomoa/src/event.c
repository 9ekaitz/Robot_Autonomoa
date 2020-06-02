#include "status.h"
#include "map.h"
#include "image.h"
#include "event.h"

void checkEvents(SDL_Renderer *render, STATUS *app, pNODO_IMG *img_header, ROUTE *route, MAP *map, PATH *fastestPath)
{
	SDL_Event event;
	PIXELKOORD point;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				app->run = SDL_FALSE;
				break;
			case SDL_MOUSEBUTTONUP:
				checkMouse(event.button, app, route, map);
				if (route->kop == 1)
				{
					point = coordToPixel(map->koord[route->points[0]]);
					load_image(img_header, render, "./media/pointer.bmp", point.x, point.y, 30, 40);
				}
				if (app->current == LA_RUTA_SE_ESTA_CALCULANDO)
				{
					*fastestPath = dijkstra(*map, route->points[0], route->points[1]);
					fillPathKoord(map->koord, fastestPath);

//					aparecerKotxe();
					app->current = ONROUTE;
				}
				break;
				//momentuz ez daukagu teklarik
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
	mouse.x = x*IMG_WIDTH/PANTAILA_ZABALERA;
	mouse.y = y*IMG_HEIGHT/PANTAILA_ALTUERA ;

	switch (event.button)
	{
		case SDL_BUTTON_LEFT:
			if (app->current == SELECT)
			{
				route->points[route->kop] = nearestPoint(map->koord, map->size, mouse);
				route->kop++;
				if (route->kop == 2)
				{
					app->current = LA_RUTA_SE_ESTA_CALCULANDO;
				}
			}
			break;

		case SDL_BUTTON_RIGHT:

			break;

		case SDL_BUTTON_MIDDLE:

			break;
	}
}
