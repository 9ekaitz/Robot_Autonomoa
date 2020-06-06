#ifndef SRC_STATUS_H_
#define SRC_STATUS_H_

typedef enum {SELECT_1, SELECT_2, ONROUTE, FINISHED}PROCCESS;

typedef struct status{
	SDL_bool run;
	PROCCESS current;
}STATUS;

#endif /* SRC_STATUS_H_ */
