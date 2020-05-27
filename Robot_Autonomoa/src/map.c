#include <stdio.h>
#include <limits.h>
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
