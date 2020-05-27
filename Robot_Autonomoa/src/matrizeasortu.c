#include <stdio.h>
#include <stdlib.h>
#include "matrizeasortu.h"

void matrizeaSortuExec()
{
	int fila[ELEMENTO_FILA_MAX];
	FILE* fitxategia = fopen("matrizea.txt", "a"); //"a" para seguir sin borrar el txt

	for (int i = 90; i < ELEMENTO_FILA_MAX; i++)
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

void matrizeaSinplifikatu()
{
	FILE *fitxategia = fopen("distancia.csv", "r");
	FILE *fitxategiaINPUT = fopen("input_U.txt", "r");
	FILE *fitxategiadest = fopen("distanciaRECT_U", "w");

	int i, zaborra, x, tmp;
	char str[256][256];


		//	fscanf(fitxategia, "%s", str[i]);
		//fscanf(fitxategiaINPUT, "%d", &x);
		//sscanf(str[z], "\"%d\",\"%d", &zaborra, &tmp);
		//	fprintf(fitxategiadest, "%s\n", str[z]);
	for (int z = 0; z < 196; z++)
	{
		i = 0;
		fscanf(fitxategia, "%s", str[0]);
		sscanf(str[0], "\"%d", &zaborra);
		while (zaborra == z +1)
		{
			fscanf(fitxategia, "%s", str[i]);
			sscanf(str[i], "\"%d", &zaborra);
			i++;
		}
		do
		{
			fscanf(fitxategiaINPUT, "%d", &x);
			if (x != -1)
			{
				for (int j = 0; j < i; j++)
				{
					sscanf(str[j], "\"%d\",\"%d", &zaborra, &tmp);
					if (x == tmp)
					{
						fprintf(fitxategiadest, "%s\n", str[j]);
					}
				}
			}
		}while ( x != -1);
	}

	fclose(fitxategiaINPUT);
	fclose(fitxategia);
	fclose(fitxategiadest);
}

void matrizeaSortu_v2()
{
	FILE *fitxategia = fopen("distanciaRECT", "r");
	FILE *fitxategiadest = fopen("gros_dat", "w");

	fpos_t position;

	int id, to, j = 0, exit;
	double data[196], tmp;
	char str[6][256];

	fgetpos(fitxategia, &position);
	for (int x = 0; x < 196; x++)
	{
		for (int i = 0; i < 196; i++)
		{
			data[i] = -1;
		}
		exit = 0;
		j = 0;
		do
		{
			fgetpos(fitxategia, &position);
			fscanf(fitxategia, "%s", str[j]);
			sscanf(str[j], "\"%d\",\"%d\",%lf", &id, &to, &tmp);
			if (id != x+1)
			{
				fsetpos(fitxategia, &position);
				exit = 1;
			}
			else
			{
				data[to-1] = tmp;
			}
			j++;
		} while (!exit);
		for (int i = 0; i < 196; i++)
		{
			fprintf(fitxategiadest, "%lf ", data[i]);
		}
		fputs("\n", fitxategiadest);
	}
	fclose(fitxategia);
	fclose(fitxategiadest);

}

void BmatrizeaSortu_v2()
{
	FILE *fitxategia = fopen("gros_dat", "r");
	FILE *fitxategiadest = fopen("gros.dat", "w");

	double data;

	for (int i = 0; i < 196; i++)
	{
		fscanf(fitxategia, "%lf ", &data);
		fwrite(&data, sizeof(double), 1, fitxategiadest);
	}

	fclose(fitxategia);
	fclose(fitxategiadest);

}

void matrizeaSortu_v2_Binario()
{
	FILE *fitxategia = fopen("distanciaRECT", "r");
	FILE *fitxategiadest = fopen("gros.dat", "w");

	fpos_t position;

	int id, to, j = 0, exit;
	double data[196], tmp;
	char str[6][256];

	fgetpos(fitxategia, &position);
	for (int x = 0; x < 196; x++)
	{
		for (int i = 0; i < 196; i++)
		{
			data[i] = -1;
		}
		exit = 0;
		j = 0;
		do
		{
			fgetpos(fitxategia, &position);
			fscanf(fitxategia, "%s", str[j]);
			sscanf(str[j], "\"%d\",\"%d\",%lf", &id, &to, &tmp);
			if (id != x+1)
			{
				fsetpos(fitxategia, &position);
				exit = 1;
			}
			else
			{
				data[to-1] = tmp;
			}
			j++;
		} while (!exit);
		for (int i = 0; i < 196; i++)
		{
			fwrite(&data[i], sizeof(double), 1, fitxategiadest);
		}
	}
	fclose(fitxategia);
	fclose(fitxategiadest);
}



