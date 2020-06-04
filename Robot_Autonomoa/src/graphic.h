#ifndef SRC_GRAPHIC_H_
#define SRC_GRAPHIC_H_

	#define PANTAILA_ALTUERA 720
	#define PANTAILA_ZABALERA 1280

	typedef struct background{		//Argazkiak eta pantailan irudikatzeko behar dutren datu guztiak
		SDL_Texture* texture;
		SDL_Rect dim, scroll;

	}BACKGROUND, *pBACKGROUND;

	typedef struct object{		//Argazkiak eta pantailan irudikatzeko behar dutren datu guztiak
		SDL_Texture* texture;
		SDL_Rect dim;

	}OBJECT;

	typedef struct Nodo_OBJ{
		OBJECT *obj;
		struct Nodo_OBJ *ptrNext;
	}NODO_OBJ, *pNODO_OBJ;

	void load_background(pBACKGROUND *background, SDL_Renderer *render, char src[], int w, int h);

	void load_image(pNODO_OBJ *header, SDL_Renderer *render, char src[], int x, int y, int w, int h);

	void load_imageData(OBJECT **image, SDL_Renderer *render, char src[], int x, int y, int w, int h);

	void load_objectInsertTop(pNODO_OBJ *header, OBJECT *object);

	void load_objectInsertBottom(pNODO_OBJ *header, OBJECT *object);

	void rectBuilder(SDL_Rect *rect, int x, int y, int w, int h);

	void drawLines(BACKGROUND *background, SDL_Renderer *render, PATH fastestPath);

	void drawLine(BACKGROUND *background, SDL_Renderer *render, PIXELKOORD src, PIXELKOORD dst);

	void load_font(pNODO_OBJ *header, SDL_Renderer *render, float cost, TTF_Font *font, SDL_Color color);

	void load_fontData(OBJECT **object, SDL_Renderer *render, TTF_Font *font, SDL_Color color, char text[], int x, int y);


	#endif /* SRC_GRAPHIC_H_ */
