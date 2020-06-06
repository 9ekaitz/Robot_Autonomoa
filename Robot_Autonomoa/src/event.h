#ifndef SRC_EVENT_H_
#define SRC_EVENT_H_

	#define SPEED 10

	void checkEvents(SDL_Renderer *render, BACKGROUND *background, STATUS *app, ROUTE *route, MAP *map);

	void checkMouse(SDL_MouseButtonEvent event, STATUS *app, ROUTE *route, MAP *map);

	void followTheLine(OBJECT *car, PATH fastestPath, PROCCESS *current);

	void moveCar( OBJECT *car, PIXELKOORD src, PIXELKOORD dst);

	int checkNode(OBJECT *car, PIXELKOORD src, PIXELKOORD dst);

	void refreshStatus(BACKGROUND *background, PROCCESS *current, SDL_Renderer *render, pNODO_OBJ *toRender,  NODO_OBJ *header, ROUTE *route, MAP *map, PATH *fastestPath, TTF_Font *font, SDL_Color color);

#endif /* SRC_EVENT_H_ */
