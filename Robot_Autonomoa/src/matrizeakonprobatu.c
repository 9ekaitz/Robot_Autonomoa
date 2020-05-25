#include <stdio.h>
#include <stdlib.h>
#include "matrizeakonprobatu.h"

void matrizeaKonprobatuExec()
{
	FILE* fitxategia = fopen("matrizea.txt", "r");
	int zenbakia;

	if (fitxategia != NULL)
	{
		for (int i = 0; i < ELEMENTO_FILA_MAX; ++i)
		{
			printf("%d. nodoaren gertukoak: ", i);
			for (int j = 0; j < ELEMENTO_FILA_MAX; ++j)
			{
				fscanf(fitxategia, "%d", &zenbakia);
				if (zenbakia != 0)
				{
					printf("%d ", j);
				}
			}
			printf("\n");
		}
	}
	else
	{
		printf("Error: fitxategia irekitzerakoan\n");
	}
	fclose(fitxategia);
}
