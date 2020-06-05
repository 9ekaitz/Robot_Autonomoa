#ifndef SRC_EVENT_H_
#define SRC_EVENT_H_

	#define SPEED 10

	void checkEvents(SDL_Renderer *render, BACKGROUND *background, STATUS *app, pNODO_OBJ *header, ROUTE *route, MAP *map, PATH *fastestPath, TTF_Font *font, SDL_Color color);

	void checkMouse(SDL_MouseButtonEvent event, STATUS *app, ROUTE *route, MAP *map);

	void followTheLine(OBJECT *car, PATH fastestPath,BACKGROUND *background);

	void moveCar( OBJECT *car, PIXELKOORD src, PIXELKOORD dst,BACKGROUND *background);

	int checkNode(OBJECT *car, PIXELKOORD src, PIXELKOORD dst);

#endif /* SRC_EVENT_H_ */
