#ifndef SRC_BASIC_H_
#define SRC_BASIC_H_

	int windowandRender(SDL_Window **window, SDL_Renderer **render, TTF_Font **font);		//Lehioa eta rendera hasieratzen du, eta leihoari ikono bat ematen dio, errorerik baldin badaude -1 bueltatuko du

	void refresh(SDL_Renderer *render);

	void launch(SDL_Renderer **render, pBACKGROUND *background, MAP **map);

	void renderBackground(SDL_Renderer **render, BACKGROUND *background);

	void renderObjects(SDL_Renderer **render, BACKGROUND *background, NODO_OBJ *header, PATH fastestPath, PROCCESS current);

	void txapar(SDL_Window *window, SDL_Renderer *render);

	void destroyBackground(pBACKGROUND *background);

	void destroyMap(MAP **map);	//Maparen datuak ezabatu

	void destroyObjects(pNODO_OBJ *header, int content);	//Objektu guztiak ezabatu

#endif /* SRC_BASIC_H_ */
