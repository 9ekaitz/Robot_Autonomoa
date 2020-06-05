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

void drawLines(NODO_IMG *img_header, SDL_Renderer *render, PATH fastestPath)
{
	SDL_SetRenderDrawColor(render, 255, 80, 80, SDL_ALPHA_OPAQUE);

	for (int i = 0; i < fastestPath.len-1; i++)
	{
		drawLine(img_header, render, fastestPath.vertex_koord[i], fastestPath.vertex_koord[i+1]);


	}

	static int x=0;


//si la X,Y de la imagen pasa la X,Y del siguiente nodo entra.

	int static kk=0;

//	if(img_header->ptrNext->ptrNext->img->dim.x >= fastestPath.vertex_koord[kk+1].x && img_header->ptrNext->ptrNext->img->dim.y >= fastestPath.vertex_koord[kk+1].y)
//	{
//		kk++;
//	}

	//kk +=caniar_de_punto(img_header, fastestPath.vertex_koord[kk], fastestPath.vertex_koord[kk+1]);

	if(caniar_de_punto(img_header, fastestPath.vertex_koord[kk], fastestPath.vertex_koord[kk+1]))
		{
		kk +=1;

		img_header->ptrNext->ptrNext->img->dim.x=fastestPath.vertex_koord[kk].x;
		img_header->ptrNext->ptrNext->img->dim.y=fastestPath.vertex_koord[kk].y;
		}


	mover_punto(img_header, fastestPath.vertex_koord[kk], fastestPath.vertex_koord[kk+1]);

}

void drawLine(NODO_IMG *img_header, SDL_Renderer *render, PIXELKOORD src, PIXELKOORD dst)
{
	if (img_header->img->scroll.x < 0)
	{
		src.x = ((float)src.x / (float)IMG_WIDTH) * PANTAILA_ZABALERA;
		src.y = ((float)src.y / (float)IMG_HEIGHT) * PANTAILA_ALTUERA;
		dst.x = ((float)dst.x / (float)IMG_WIDTH) * PANTAILA_ZABALERA;
		dst.y = ((float)dst.y / (float)IMG_HEIGHT) * PANTAILA_ALTUERA;
	}
	else
	{
		src.x -= img_header->img->scroll.x;
		src.y -= img_header->img->scroll.y;
		dst.x -= img_header->img->scroll.x;
		dst.y -= img_header->img->scroll.y;



	}

	SDL_RenderDrawLine(render, src.x, src.y, dst.x, dst.y);
	SDL_RenderDrawLine(render, src.x, src.y+1, dst.x-1, dst.y);
//	SDL_RenderDrawLine(render, src.x, src.y+2, dst.x-2, dst.y);
//	SDL_RenderDrawLine(render, src.x, src.y+3, dst.x-3, dst.y);
	SDL_RenderDrawLine(render, src.x+1, src.y, dst.x, dst.y-1);
//	SDL_RenderDrawLine(render, src.x+2, src.y, dst.x, dst.y-2);
//	SDL_RenderDrawLine(render, src.x+3, src.y, dst.x, dst.y-3);

}

void mover_punto(NODO_IMG *img_header, PIXELKOORD src, PIXELKOORD dst)
{
	int vel=10;
	int x=img_header->ptrNext->ptrNext->img->dim.x;
	int y=img_header->ptrNext->ptrNext->img->dim.y;

			//	src.x -= img_header->img->scroll.x;
			//src.y -= img_header->img->scroll.y;

	float m=(float)(dst.y-src.y)/(float)(dst.x-src.x);//calculamos la malda


	if(m<0)
	{
	vel=vel*-1;
	}

	if(dst.x>src.x&&src.y>dst.y)
	{
		vel=vel*-1;
	}


	if(m>0&&dst.x<src.x&&dst.y<src.y)
	{
	vel=vel*-1;
	}

	x += vel;

	y +=vel*m;

//y=m*(x-src.x)+src.y;


			//img_header->img->scroll.x = src.x;
			//img_header->img->scroll.y = src.y;

			img_header->ptrNext->ptrNext->img->dim.x=x;
			img_header->ptrNext->ptrNext->img->dim.y=y;

SDL_Delay(100);

}

int caniar_de_punto(NODO_IMG *img_header, PIXELKOORD src, PIXELKOORD dst)
{
		int variable = 0;

		int vel=10;

		int x=img_header->ptrNext->ptrNext->img->dim.x;//de la foto
		int y=img_header->ptrNext->ptrNext->img->dim.y;//de la foto



			//	src.x -= img_header->img->scroll.x;
				//src.y -= img_header->img->scroll.y;

		float m=(float)(dst.y-src.y)/(float)(dst.x-src.x);//calculamos la malda


		if(m<0)
		{
		vel=vel*-1;
		}

//		if(dst.x>src.x&&src.y>dst.y)
//		{
//			vel=vel*-1;
//
//		}
		/*
		//este se usa
		if (m>0&&vel>0)
		{

				if(m>0&&dst.x<src.x&&dst.y<src.y)
				{
				vel=vel*-1;
				}

		}

		//estese usa
			if (m>0&&vel<0) {

				if (x <=dst.x && y <= dst.y  )
				{
					variable=1;
				}
			}

			if(m<=0 && vel<=0)
			{
				if (x<=dst.x && y>=dst.y)
				{
					variable=1;

				}
			}









if (m<0 && vel>0) {

	if (x <=dst.x && y >= dst.y  )
		{
			variable=1;
		}

}

*/

//mira aqui tonto

		if(vel<=0)
	{

		if(img_header->ptrNext->ptrNext->img->dim.x <= dst.x && img_header->ptrNext->ptrNext->img->dim.y <= dst.y)
			{
			variable=1;
			}

	}else{
		if(img_header->ptrNext->ptrNext->img->dim.x >= dst.x && img_header->ptrNext->ptrNext->img->dim.y >= dst.y)
			{
			variable=1;
			}
	}





	return variable;
}




