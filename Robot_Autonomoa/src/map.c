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

int nearestPoint(KOORD koord[], int dim, PIXELKOORD mouse)
{
	int pos;
	double min = INT_MAX, dist;
	KOORD tmp;
	tmp = pixelToCoord(mouse);
	for (int i = 0; i < dim; i++)
	{

		dist = distance(koord[i].x, koord[i].y, tmp.x, tmp.y);
		if (dist < min)
		{
			min = dist;
			pos = i;
		}
	}

	return pos;
}

KOORD pixelToCoord(PIXELKOORD pixel)
{
	double gap_x, gap_y, width_c, height_c;

	KOORD Upper_Left;//A
	KOORD Lower_Left;//B
	KOORD Upper_Right;//c
	KOORD result;

	//A
	Upper_Left.x=-1.9802276;
	Upper_Left.y=43.3271173;
	//B
	Lower_Left.x=-1.9802276;
	Lower_Left.y=43.3206861;
	//C
	Upper_Right.x=-1.9650484;
	Upper_Right.y=43.3271173;


	//creo los modulos para saber las distancias
	height_c = sqrt(pow(Upper_Left.x-Lower_Left.x,2)+pow(Upper_Left.y-Lower_Left.y,2));
	width_c = sqrt(pow(Upper_Left.x-Upper_Right.x,2)+pow(Upper_Left.y-Upper_Right.y,2));


	//Pixel bakoitzeko koordenatu tartea
	gap_x = width_c/(double)IMG_WIDTH;
	gap_y = height_c/(double)IMG_HEIGHT;

	//saco la cordenada X e Y de pixeles a las de gps "EPSG:3857"
	result.x = Upper_Left.x+(gap_x*pixel.x);
	result.y = Upper_Left.y-(gap_y*pixel.y);

	return result;
}

double distance(double lon1, double lat1, double lon2, double lat2)
{
	double dLat, dLon, a, d, c;

	dLat = lat2 * PI / 180 - lat1 * PI / 180;
	dLon = lon2 * PI / 180 - lon1 * PI / 180;

	a = sin(dLat/2) * sin(dLat/2) + cos(lat1 * PI / 180) * cos(lat2 * PI / 180) * sin(dLon/2) * sin(dLon/2);
	c = 2 * atan2(sqrt(a), sqrt(1-a));
	d = EARTH_R * c;

	return d * 1000;
}
