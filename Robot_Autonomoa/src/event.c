#include "image.h"
#include "event.h"
#include "math.h"

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

							if((*img_header)->ptrNext->img->dim.y<=PANTAILA_ALTUERA/2) //esto comprueba si el punto esta centrado en la pantalla
							{
								if((*img_header)->img->scroll.y >=0){
								(*img_header)->img->scroll.y -= 30;
								}else{
									(*img_header)->ptrNext->img->dim.y -=5; //resta 5 al pixel y del punto y lo mueve hacia arriba
								}
							}else{
								(*img_header)->ptrNext->img->dim.y -=5; //resta 5 al pixel y del punto y lo mueve hacia arriba
							}

							break;
						case SDL_SCANCODE_DOWN:
							if((*img_header)->ptrNext->img->dim.y>=PANTAILA_ALTUERA/2) //esto comprueba si el punto esta centrado en la pantalla
							{
								if((*img_header)->img->scroll.y + PANTAILA_ALTUERA<= IRUDIAREN_ALTUERA)
								{
								(*img_header)->img->scroll.y += 30;
								}
								else{
									(*img_header)->ptrNext->img->dim.y +=5; //suma 5 al pixel y del punto y lo mueve hacia abajo

								}
							}else//sin el else no podriamos mover el punto mas una vez
							{
								(*img_header)->ptrNext->img->dim.y +=5; //suma 5 al pixel y del punto y lo mueve hacia abajo


							}


							break;
						case SDL_SCANCODE_RIGHT:


							if((*img_header)->ptrNext->img->dim.x>=PANTAILA_ZABALERA/2) //esto comprueba si el punto esta centrado en la pantalla
							{
								if(((*img_header)->img->scroll.x + PANTAILA_ZABALERA <= IRUDIAREN_ZABALERA))//esto hace que la pantalla no se valla a la derecha
									{
									(*img_header)->img->scroll.x += 30; //hace que el scrol se pueda mover a la derecha
									}else{
										(*img_header)->ptrNext->img->dim.x +=5;//suma 5 al pixel x del punto y lo mueve a la derecha

									}
							}else//sin el else no podriamos mover el punto mas de una vez
							{
								(*img_header)->ptrNext->img->dim.x +=5;//suma 5 al pixel x del punto y lo mueve a la derecha
							}


							break;
						case SDL_SCANCODE_LEFT:
							if((*img_header)->ptrNext->img->dim.x<=PANTAILA_ZABALERA/2) //esto comprueba si el punto esta centrado en la pantalla
							{
								if((*img_header)->img->scroll.x >=0) //esto hace que la pantalla no se valla a la izquierda
								{
								(*img_header)->img->scroll.x -= 30; //hace que el scrol se pueda mover a la izquierda
								}
								else
								{

									(*img_header)->ptrNext->img->dim.x -=5; //resta 5 al pixel x del punto y lo mueve a la izquierda
								}
							}
							else//sin el else no podriamos mover el punto mas de una vez
							{
								(*img_header)->ptrNext->img->dim.x -=5;//resta 5 al pixel x del punto y lo mueve a la izquierda
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
