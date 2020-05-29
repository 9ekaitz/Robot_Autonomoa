#ifndef SRC_MAP_H_
#define SRC_MAP_H_

	#define MAX_MAP_LEN 200
	#define EARTH_R 6378.137
	#define PI 3.14159265358979323846
	#define IMG_HEIGHT 2912
	#define IMG_WIDTH 6873

	typedef struct koord{
		double x, y;
	}KOORD;

	typedef struct PixelKoord{
		int x, y;
	}PIXELKOORD;

	typedef struct map{
		KOORD koord[MAX_MAP_LEN];
		double mapMatrix[MAX_MAP_LEN][MAX_MAP_LEN];
		int size;
	}MAP;

	typedef struct route{
		int points[2];
		int kop;
	}ROUTE;

	typedef struct path{
		float cost;
		int vertex[MAX_MAP_LEN];
		int len;
	}PATH;


	void load_map(MAP **map, char mapDat[], char koordDat[]);

	int nearestPoint(KOORD koord[], int dim, PIXELKOORD mouse);

	KOORD pixelToCoord(PIXELKOORD pixel);

	double distance(double lon1, double lat1, double lon2, double lat2);

	PATH dijkstra(MAP map, int start, int end);

	void copyPath(int *destVertex, int *destLen, int *srcVertex, int srcLen);

#endif /* SRC_MAP_H_ */
