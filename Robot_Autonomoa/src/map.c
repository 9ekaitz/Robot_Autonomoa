#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include "map.h"

void load_map(MAP **map, char mapDat[], char koordDat[])
{
	double read;
	MAP *tmp = (MAP*) malloc(sizeof(MAP));
	KOORD *coords;
	FILE *mapFile, *koordFile;

	mapFile = fopen(mapDat, "r"); //konexioen matrizea
	coords = (KOORD*) malloc(sizeof(KOORD) * tmp->size);

	if (mapFile > 0)
	{
		fread(&tmp->size, sizeof(int), 1, mapFile);
		coords = (KOORD*) malloc(sizeof(KOORD) * tmp->size);
		tmp->koord = coords;

		for (int i = 0; i < tmp->size; i++)
		{
			for (int j = 0; j < tmp->size; j++)
			{
				fread(&read, sizeof(double), 1, mapFile);
				if (read == -1)
					tmp->mapMatrix[i][j] = INT_MAX;
				else
					tmp->mapMatrix[i][j] = read;
			}
		}
		fclose(mapFile);
		*map = tmp;
		koordFile = fopen(koordDat, "rb"); //koordenatuena ireki eta jaso matrizean
		if (koordFile > 0)
		{
			for (int i = 0; i < tmp->size; i++)
			{
				fread(&tmp->koord[i].x, sizeof(double), 1, koordFile);
				fread(&tmp->koord[i].y, sizeof(double), 1, koordFile);
			}
			fclose(koordFile);
			*map = tmp;

			printf("%lf, %lf", tmp->koord[27].x, tmp->koord[90].y);
		}
	}
}

int nearestPoint(KOORD koord[], int dim, PIXELKOORD mouse)
{
	int pos;
	double min = INT_MAX, dist;
	KOORD tmp;
	tmp = pixelToCoord(mouse);
	for (int i = 0; i < dim; i++) //Puntu guztietara dagoen puntuetako distantziak begiratzen dira
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

	KOORD Upper_Left; //A
	KOORD Lower_Left; //B
	KOORD Upper_Right; //c
	KOORD result;

	//A
	Upper_Left.x = -1.9811692;
	Upper_Left.y = 43.3270931;
	//B
	Lower_Left.x = -1.9811692;
	Lower_Left.y = 43.3210206;
	//C
	Upper_Right.x = -1.9653983;
	Upper_Right.y = 43.3270931;

	//creo los modulos para saber las distancias
	height_c = sqrt(
			pow(Upper_Left.x - Lower_Left.x, 2)
					+ pow(Upper_Left.y - Lower_Left.y, 2));
	width_c = sqrt(
			pow(Upper_Left.x - Upper_Right.x, 2)
					+ pow(Upper_Left.y - Upper_Right.y, 2));

	//Pixel bakoitzeko koordenatu tartea
	gap_x = width_c / (double) IMG_WIDTH;
	gap_y = height_c / (double) IMG_HEIGHT;

	//saco la cordenada X e Y de pixeles a las de gps "EPSG:3857"
	result.x = Upper_Left.x + (gap_x * pixel.x);
	result.y = Upper_Left.y - (gap_y * pixel.y);

	return result;
}

double distance(double lon1, double lat1, double lon2, double lat2)
{
	double dLat, dLon, a, d, c;

	dLat = lat2 * PI / 180 - lat1 * PI / 180;
	dLon = lon2 * PI / 180 - lon1 * PI / 180;

	a = sin(dLat / 2) * sin(dLat / 2)
			+ cos(lat1 * PI / 180) * cos(lat2 * PI / 180) * sin(dLon / 2)
					* sin(dLon / 2);
	c = 2 * atan2(sqrt(a), sqrt(1 - a));
	d = EARTH_R * c;

	return d * 1000;
}

PIXELKOORD coordToPixel(KOORD point)
{
	double gap_x, gap_y, width_c, height_c;

	KOORD Upper_Left; //A
	KOORD Lower_Left; //B
	KOORD Upper_Right; //c
	PIXELKOORD result;

	//A
	Upper_Left.x = -1.9811692;
	Upper_Left.y = 43.3270931;
	//B
	Lower_Left.x = -1.9811692;
	Lower_Left.y = 43.3210206;
	//C
	Upper_Right.x = -1.9653983;
	Upper_Right.y = 43.3270931;

	//creo los modulos para saber las distancias
	width_c = sqrt(
			pow(Upper_Left.x - Upper_Right.x, 2)
					+ pow(Upper_Left.y - Upper_Right.y, 2));
	height_c = sqrt(
			pow(Upper_Left.x - Lower_Left.x, 2)
					+ pow(Upper_Left.y - Lower_Left.y, 2));

	//calculo cuntos tengo que sumar a la cordenada A para llegar a la cordenada C
	gap_x = width_c / IMG_WIDTH;
	gap_y = height_c / IMG_HEIGHT;

	result.x = (point.x - Upper_Left.x) / gap_x;
	result.y = ((point.y - Upper_Left.y) / -gap_y);	//+1 eginez pixela hobeta

	return result;
}

PATH dijkstra(MAP map, int start, int end)
{
	PATH paths[map.size];
	int infinite = INT_MAX;
	int visited[map.size];
	int min, pos, min_pos;

	//iniciar todo ha 0
	for (int i = 0; i < map.size; i++)
	{
		paths[i].cost = infinite;
		paths[i].len = 0;
		visited[i] = 0;
		if (map.mapMatrix[start][i] < infinite)
		{
			paths[i].cost = map.mapMatrix[start][i];
			paths[i].vertex[paths[i].len] = start;
			paths[i].len++;
		}
	}

	paths[start].cost = 0;
	paths[start].vertex[0] = start;
	paths[start].len = 1;
	visited[start] = 1;
	while (!visited[end])
	{
		min = start;
		min_pos = start;
		for (pos = 0; pos < map.size; pos++)
		{
			if (visited[pos])
			{
				//j es la letra a la que estas mirando
				//mira la siguiente ruta mas pequeña
				for (int j = 0; j < map.size; j++)
				{
					if (!visited[j]
							&& (map.mapMatrix[pos][j] + paths[pos].cost)
									< (map.mapMatrix[min_pos][min]
											+ paths[min_pos].cost))
					{
						min = j;
						min_pos = pos;
					}
				}
			}
		}
		//comprueba si la nueva ruta es mas pequeña para ir a un nodo que la que ya teniamos
		for (int i = 0; i < map.size; i++)
		{
			if (map.mapMatrix[min][i] + paths[min].cost < paths[i].cost)
			{
				paths[i].cost = map.mapMatrix[min][i] + paths[min].cost;
				copyPath(paths[i].vertex, &paths[i].len, paths[min].vertex,
						paths[min].len);
				paths[i].vertex[paths[i].len] = min;
				paths[i].len++;
			}
		}
		visited[min] = 1;				//marcas el nodo como visitado
	}
	paths[end].vertex[paths[end].len] = end;
	paths[end].len++;
	return paths[end];
}

void copyPath(int *destVertex, int *destLen, int *srcVertex, int srcLen)
{
	for (int i = 0; i < srcLen; i++)
	{
		*(destVertex + i) = *(srcVertex + i);
	}
	*destLen = srcLen;
}

void fillPathKoord(KOORD map[], PATH *fastestPath)
{
	for (int i = 0; i < fastestPath->len; i++)
	{
		fastestPath->vertex_koord[i] = coordToPixel( map[fastestPath->vertex[i]]); //id artu eta pixeletatik koordenatuetara pasa bere koordenatuak emanaz
	}
}

PATH A_star(MAP map, int start, int end)
{
	PATH paths[map.size];
	int infinite = INT_MAX;
	int visited[map.size];
	int min, pos, min_pos;

	double heuristics[map.size];

	//iniciar todo ha 0
	for (int i = 0; i < map.size; i++)
	{
		paths[i].cost = infinite;
		paths[i].len = 0;
		visited[i] = 0;
		if (map.mapMatrix[start][i] < infinite)
		{
			paths[i].cost = map.mapMatrix[start][i];
			paths[i].vertex[paths[i].len] = start;
			paths[i].len++;
		}
		heuristics[i] = distance(map.koord[i].x, map.koord[i].y,
				map.koord[end].x, map.koord[end].y);
	}

	paths[start].cost = 0;
	paths[start].vertex[0] = start;
	paths[start].len = 1;
	visited[start] = 1;
	while (!visited[end])
	{
		min = start;
		min_pos = start;
		for (pos = 0; pos < map.size; pos++)
		{
			if (visited[pos])
			{
				//j es la letra a la que estas mirando
				//mira la siguiente ruta mas pequeña
				for (int j = 0; j < map.size; j++)
				{
					if (!visited[j]
							&& (map.mapMatrix[pos][j] + paths[pos].cost
									+ heuristics[j])
									< (map.mapMatrix[min_pos][min]
											+ paths[min_pos].cost)
											+ heuristics[min])
					{
						min = j;
						min_pos = pos;
					}
				}
			}
		}
		//comprueba si la nueva ruta es mas pequeña para ir a un nodo que la que ya teniamos
		for (int i = 0; i < map.size; i++)
		{
			if (map.mapMatrix[min][i] + paths[min].cost < paths[i].cost)
			{
				paths[i].cost = map.mapMatrix[min][i] + paths[min].cost;
				copyPath(paths[i].vertex, &paths[i].len, paths[min].vertex,
						paths[min].len);
				paths[i].vertex[paths[i].len] = min;
				paths[i].len++;
			}
		}
		visited[min] = 1;				//marcas el nodo como visitado
	}
	paths[end].vertex[paths[end].len] = end;
	paths[end].len++;
	return paths[end];
}
