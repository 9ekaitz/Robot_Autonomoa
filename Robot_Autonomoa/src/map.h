#ifndef SRC_MAP_H_
#define SRC_MAP_H_

	#define MAX_MAP_LEN 200

	typedef struct koord{
		double x, y;
	}KOORD;

	typedef struct map{
		KOORD koord[MAX_MAP_LEN];
		double mapMatrix[MAX_MAP_LEN][MAX_MAP_LEN];
		int size;
	}MAP;

	void load_map(MAP **map, char mapDat[], char koordDat[]);

#endif /* SRC_MAP_H_ */
