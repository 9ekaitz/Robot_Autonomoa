#ifndef SRC_BASIC_H_
#define SRC_BASIC_H_

	#define PANTAILA_ALTUERA 720
	#define PANTAILA_ZABALERA 1280

	typedef struct Image{		//Argazkiak eta pantailan irudikatzeko behar dutren datu guztiak
		SDL_Texture* texture;
		SDL_Rect dim;
	}IMG;

	typedef struct Nodo_IMG{
		IMG *img;
		struct Nodo_IMG *ptrNext;
	}NODO_IMG, *pNODO_IMG;


	int windowandRender(SDL_Window **window, SDL_Renderer **render);		//Lehia eta rendera hasieratzen du, eta leihoari ikono bat ematen dio, errorerik baldin badaude 1 bueltatuko du

	void close(SDL_Window **window, SDL_Renderer **render);

	void refresh(SDL_Renderer **render);

	int load_imageData(IMG **image, SDL_Renderer *render, char src[], int x, int y, int w, int h);

	void rectBuilder(SDL_Rect *rect, int x, int y, int w, int h);

#endif /* SRC_BASIC_H_ */
