#ifndef SRC_STATUS_H_
#define SRC_STATUS_H_

typedef enum {SELECT, LA_RUTA_SE_ESTA_CALCULANDO, ONROUTE}PROCCESS;

typedef struct status{
	SDL_bool run;
	PROCCESS current;
}STATUS;

#endif /* SRC_STATUS_H_ */
