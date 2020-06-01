#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "map.h"

void load_map(MAP **map, char src[])
{
	double read;
	MAP *tmp = (MAP *)malloc(sizeof(MAP));
	FILE *mapFile, *koordFile;
	char mapDat[64];
	char koordDat[64];

	strcpy(koordDat, src);
	//strcat(src, ".dat");
	strcat(koordDat, "_koord.dat");

	mapFile= fopen(src, "r");

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

	}

}
