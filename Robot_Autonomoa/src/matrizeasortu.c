#include <stdio.h>
#include <stdlib.h>
#include "matrizeasortu.h"

void matrizeaSortuExec()
{
	int fila[ELEMENTO_FILA_MAX];
	FILE* fitxategia = fopen("matrizea.txt", "w"); //"a" para seguir sin borrar el txt

	for (int i = 0; i < ELEMENTO_FILA_MAX; i++)
	{
		filaJaso(fila, i);
		FilaSortu(fila, fitxategia);
		filaGarbitu(fila);
	}
	fclose(fitxategia);
}

void FilaSortu(int fila[], FILE* fitxategia)
{
	if (fitxategia != NULL)
	{
		for (int i = 0; i < ELEMENTO_FILA_MAX; i++) /////////////
		{
			fprintf(fitxategia, "%d ", fila[i]);
		}
		fprintf(fitxategia, "\n");
	}
	else
	{
		printf("Error: fitxategia irekitzean\n");
	}
}

void filaJaso(int fila[], int punto)
{
	int j = 0, lotutakoPuntua = 0, loturak[ELEMENTO_FILA_MAX], i = 0;
	char str[128];

	printf("\n%d. Nodoaren loturak (-1 gelditzeko): \n", punto);

	while (lotutakoPuntua != -1)
	{
		fgets(str, 128, stdin);
		sscanf(str, "%d", &lotutakoPuntua);

		if (lotutakoPuntua != -1)
		{
			loturak[j] = lotutakoPuntua;
			j++;
		}
	}
	//MATRIZEKO FILA ARRAYRA PASA
	j = 0;
	while (i < ELEMENTO_FILA_MAX)
	{
		if (loturak[j] == i)
		{
			fila[i] = -1;
			j++;
		}
		else
		{
			fila[i] = 0;
		}
		i++;
	}
}

void filaGarbitu(int fila[])
{
	for (int i = 0; i < ELEMENTO_FILA_MAX; i++)
	{
		fila[i] = 0;
	}
}

