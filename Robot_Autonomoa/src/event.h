#ifndef SRC_EVENT_H_
#define SRC_EVENT_H_

	void checkEvents(SDL_Renderer *render, BACKGROUND *background, STATUS *app, pNODO_OBJ *header, ROUTE *route, MAP *map, PATH *fastestPath, TTF_Font *font, SDL_Color color);

	void checkMouse(SDL_MouseButtonEvent event, STATUS *app, ROUTE *route, MAP *map);

#endif /* SRC_EVENT_H_ */
