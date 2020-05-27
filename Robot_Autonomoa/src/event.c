#include "image.h"
#include "event.h"

void checkEvents(SDL_bool* run, pNODO_IMG *img_header)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			//*Pantaila += 1;//esto no sirve de nada
			case SDL_QUIT:
				*run = SDL_FALSE;
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)		// SWITCH PARA LAS PULSACIONES DE TECLAS
				{
				case SDL_SCANCODE_UP:
					(*img_header)->img->scroll.y -= 15;
					break;
				case SDL_SCANCODE_DOWN:
					(*img_header)->img->scroll.y += 15;
					break;
				case SDL_SCANCODE_RIGHT:
					(*img_header)->img->scroll.x += 15;
					break;
				case SDL_SCANCODE_LEFT:
					(*img_header)->img->scroll.x -= 15;
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
						rectBuilder(&(*img_header)->img->scroll, 0,0, PANTAILA_ZABALERA*2, PANTAILA_ALTUERA*2);
						break;
					case SDL_SCANCODE_ESCAPE:
						*run = SDL_FALSE;
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
