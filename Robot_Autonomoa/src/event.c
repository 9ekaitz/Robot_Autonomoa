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

void moveCar(PIXELKOORD src, PIXELKOORD dst, OBJECT *car)
{
	int speed;

	int *x = &car->dim.x;
	int *y = &car->dim.y;


	float m = (float)(dst.y-src.y)/(float)(dst.x-src.x);	//Malda

	if (src.x > dst.x)	// edozein norazkoan funztionatzeko
	{
		speed = -SPEED;
	}

	*x = *x + speed;
	*y = *y +speed*m;


	SDL_Delay(100);

}




int caniar_de_punto(OBJECT *car, PIXELKOORD src, PIXELKOORD dst)
{
		int variable = 0;

		int vel=10;

		int x= car->dim.x;//de la foto
		int y= car->dim.y;//de la foto


		float m=(float)(dst.y-src.y)/(float)(dst.x-src.x);//calculamos la malda


		if(m<0)
		{
			vel=vel*-1;
		}
		if(vel<=0)
		{
			if( car->dim.x <= dst.x && car->dim.y <= dst.y)
			{
				variable=1;
			}
		}
		else
		{
			if(car->dim.x >= dst.x && car->dim.y >= dst.y)
			{
				variable=1;
			}
		}

	return variable;
}
