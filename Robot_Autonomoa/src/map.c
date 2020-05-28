#include <stdio.h>
#include <limits.h>
#include <math.h>
#include "map.h"

void load_map(MAP **map, char mapDat[], char koordDat[])
{
	double read;
	MAP *tmp = (MAP *)malloc(sizeof(MAP));
	FILE *mapFile, *koordFile;

	mapFile= fopen(mapDat, "r");

	if (mapFile > 0)
	{
		fread(&tmp->size, sizeof(int), 1, mapFile);

		for (int i = 0; i < tmp->size; i++)
		{
			for (int j = 0; j < tmp->size; j++)
			{
				fread(&read, sizeof(double), 1, mapFile);
				if (read == -1) tmp->mapMatrix[i][j] = INT_MAX;
				else tmp->mapMatrix[i][j] = read;
			}
		}

		*map = tmp;
		fclose(mapFile);
	}

	koordFile = fopen(koordDat, "r");
	if (koordFile > 0)
	{
		for (int i = 0; i < tmp->size; i++)
		{
			fread(&read, sizeof(double), 1, koordFile);
			tmp->koord[i].x = read;
			fread(&read, sizeof(double), 1, koordFile);
			tmp->koord[i].y = read;
		}
		fclose(koordFile);
	}
}

void nearestPoint(KOORD koord, int dim, PIXELKOORD mouse)
{
	for (int i = 0; i < dim; i++)
	{

	}
	distance();


}

KOORD pixelToCoord()
{
	//crear extructura
	printf("esta haciendo cosas de matrices\n");

	int pixely=2;
	int pixelx=2;

	int x=1;
	//esto es lo que metes en la funcion
	double coordenaday=0;
	double coordenadax=0;

	int tamanodeimagenX=10210;
	int tamanodeimagenY=4993;

	double modulo_ab=0;
	double modulo_ac=0;

	double cachosy;
	double cachosx;

	KOORD Upper_Left;//A
	KOORD Lower_Left;//B
	KOORD Upper_Right;//C


	//A
	Upper_Left.x=-1.9809783;
	Upper_Left.y=43.3276273;

	//B
	Lower_Left.x=-1.9809783;
	Lower_Left.y=43.3197019;

	//C
	Upper_Right.x=-1.9647722;
	Upper_Right.y=43.3276273;




//creo los modulos para saber las distancias
modulo_ab=sqrt(pow(Upper_Left.x-Lower_Left.x,2)+pow(Upper_Left.y-Lower_Left.y,2));



modulo_ac=sqrt(pow(Upper_Left.x-Upper_Right.x,2)+pow(Upper_Left.y-Upper_Right.y,2));


//calculo cuntos tengo que sumar a la cordenada A para llegar a la cordenada C
cachosy=modulo_ab/tamanodeimagenY;
cachosx=modulo_ac/tamanodeimagenX;


//aqui podria estar mal

//saco la cordenada X e Y de pixeles a las de gps

coordenaday=Upper_Left.y-(cachosy*pixely);

coordenadax=Upper_Left.x+(cachosx*pixelx);


    return 0;
}

double distance(double lat1, double lat2, double lon1, double lon2)
{
	double dLat, dLon, a, d, c;

	dLat = lat2 * PI / 180 - lat1 * PI / 180;
	dLon = lon2 * PI / 180 - lon1 * PI / 180;

	a = sin(dLat/2) * sin(dLat/2) + cos(lat1 * PI / 180) * cos(lat2 * PI / 180) * sin(dLon/2) * sin(dLon/2);
	c = 2 * atan2(sqrt(a), sqrt(1-a));
	d = EARTH_R * c;

	return d * 1000; // meters
}
