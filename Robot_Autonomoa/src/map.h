#ifndef SRC_MAP_H_
#define SRC_MAP_H_

	#define MAX_MAP_LEN 200

	typedef struct koord{
		double x, y;
	}KOORD;

	typedef struct map{
		KOORD koord;
		double mapMatrix[MAX_MAP_LEN][MAX_MAP_LEN];
		int size;
	}MAP;

	typedef struct punto_azul{

		KOORD koord;

	}PUNTO_AZUL;

	void load_map(MAP **map, char src[]);

#endif /* SRC_MAP_H_ */
