#ifndef SRC_BASIC_H_
#define SRC_BASIC_H_

	#define PANTAILA_ALTUERA 720
	#define PANTAILA_ZABALERA 1280

	int windowandRender(SDL_Window **window, SDL_Renderer **render);		//Lehioa eta rendera hasieratzen du, eta leihoari ikono bat ematen dio, errorerik baldin badaude -1 bueltatuko du

	void refresh(SDL_Renderer *render);

	void launch(SDL_Renderer **render, pNODO_IMG *img_header);

	void renderObjects(SDL_Renderer **render, NODO_IMG *img_header);

	void txapar(SDL_Window *window, SDL_Renderer *render);

#endif /* SRC_BASIC_H_ */
