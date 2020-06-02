#ifndef SRC_EVENT_H_
#define SRC_EVENT_H_

	void checkEvents(SDL_Renderer *render, STATUS *app, pNODO_IMG *img_header, ROUTE *route, MAP *map, PATH *fastestPath);

	void checkMouse(SDL_MouseButtonEvent event, STATUS *app, ROUTE *route, MAP *map);

#endif /* SRC_EVENT_H_ */
