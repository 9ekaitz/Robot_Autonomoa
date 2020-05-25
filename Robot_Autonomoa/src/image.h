#ifndef SRC_IMAGE_H_
#define SRC_IMAGE_H_

#define MAP "./media/Interfaz.bmp"

	typedef struct Image{		//Argazkiak eta pantailan irudikatzeko behar dutren datu guztiak
		SDL_Texture* texture;
		SDL_Rect dim;
	}IMG;

	typedef struct Nodo_IMG{
		IMG *img;
		struct Nodo_IMG *ptrNext;
	}NODO_IMG, *pNODO_IMG;

	void load_image(pNODO_IMG *img_header, SDL_Renderer *render, char src[], int x, int y, int w, int h);

	int load_imageData(IMG **image, SDL_Renderer *render, char src[], int x, int y, int w, int h);

	void load_imageInsertTop(pNODO_IMG *img_header, IMG *image);

	void load_imageInsertBottom(pNODO_IMG *img_header, IMG *image);

	void rectBuilder(SDL_Rect *rect, int x, int y, int w, int h);

#endif /* SRC_IMAGE_H_ */
