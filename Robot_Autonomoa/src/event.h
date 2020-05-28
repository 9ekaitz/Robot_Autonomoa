#ifndef SRC_EVENT_H_
#define SRC_EVENT_H_

	typedef struct PixelKoord{
		int x, y;
	}PIXELKOORD;

	void checkMouse(PIXELKOORD *mouse, IMG *background);

	void checkEvents(SDL_bool* run, pNODO_IMG *img_header);

#endif /* SRC_EVENT_H_ */
