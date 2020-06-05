#include "status.h"
#include "map.h"
#include "graphic.h"
#include "event.h"

void checkEvents(SDL_Renderer *render, BACKGROUND *background, STATUS *app, pNODO_OBJ *header, ROUTE *route, MAP *map, PATH *fastestPath, TTF_Font *font, SDL_Color color)
{
	SDL_Event event;
	PIXELKOORD endPoint, startPoint;

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
					startPoint = coordToPixel(map->koord[route->points[0]]);
					load_image(header, render, "./media/pointer.bmp", startPoint.x, startPoint.y, 30, 40);
				}
				if (route->kop == 2)
				{
					startPoint = coordToPixel(map->koord[route->points[0]]);
					endPoint = coordToPixel(map->koord[route->points[1]]);
					load_image(header, render, "./media/meta.bmp", endPoint.x, endPoint.y, 37, 40);
					load_image(header, render, "./media/punto.bmp", startPoint.x, startPoint.y, 40, 30);
					route->kop = 0;
				}
				if (app->current == LA_RUTA_SE_ESTA_CALCULANDO)
				{
					*fastestPath = A_star(*map, route->points[0], route->points[1]);
					fillPathKoord(map->koord, fastestPath);
					load_font(header, render, fastestPath->cost, font, color);
//					aparecerKotxe();
					app->current = ONROUTE;
				}
				break;
				//momentuz ez daukagu teklarik
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)		// SWITCH PARA LAS PULSACIONES DE TECLAS
				{
				case SDL_SCANCODE_UP:
					if (background->scroll.y >= 15)
					{
						background->scroll.y -= 15;
					}
					break;
				case SDL_SCANCODE_DOWN:
					if (background->scroll.y + PANTAILA_ALTUERA <= background->dim.h - 15)
					{
						background->scroll.y += 15;
					}
					break;
				case SDL_SCANCODE_RIGHT:
					if (background->scroll.x + PANTAILA_ZABALERA <= background->dim.w-15)
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
						rectBuilder(&background->scroll, 0,0, PANTAILA_ZABALERA, PANTAILA_ALTUERA);
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

void moveCar( OBJECT *car, PIXELKOORD src, PIXELKOORD dst, BACKGROUND *background)
{
	int speed = SPEED;

	int debug_x, debug_y;
	int *x = &car->dim.x;
	int *y = &car->dim.y;

	debug_x = car->dim.x;
	debug_y = car->dim.y;


	float m = (float)(dst.y-*y)/(float)(dst.x-*x);	//Malda

	if (src.x > dst.x)	// edozein norazkoan funztionatzeko
	{
		speed = -speed;
	}

	*x = *x + speed;
	*y = *y +speed*m;

	int xx=*x;
	int yy=*y;

	background->scroll.x=xx-PANTAILA_ZABALERA/2;



		background->scroll.y=yy-PANTAILA_ALTUERA/2 ;


	SDL_Delay(100);
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

void followTheLine(OBJECT *car, PATH fastestPath, BACKGROUND *background)
{
	static int x=0;

	//si la X,Y de la imagen pasa la X,Y del siguiente nodo entra.
	//kk +=caniar_de_punto(img_header, fastestPath.vertex_koord[kk], fastestPath.vertex_koord[kk+1]);

	if(checkNode(car, fastestPath.vertex_koord[x], fastestPath.vertex_koord[x+1]))
	{
		x +=1;
	}
	moveCar(car, fastestPath.vertex_koord[x], fastestPath.vertex_koord[x+1],background);
}
