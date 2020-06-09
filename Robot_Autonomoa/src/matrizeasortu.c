#include <stdio.h>
#include <stdlib.h>
#include "matrizeasortu.h"

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

void matrizeaSortu_v2_Binario()
{
	FILE *fitxategia = fopen("distanciaRECT", "r");
	FILE *fitxategiadest = fopen("gros.dat", "w");

	fpos_t position;

	int id, to, j = 0, exit, kop = 196;
	double data[196], tmp;
	char str[6][256];

	fwrite(&kop, sizeof(int), 1, fitxategiadest);

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

void koordAtera()
{
	FILE *fitxategia = fopen("coord.csv", "r");
	FILE *fitxategiadest = fopen("gros_koord.dat", "w");

	int id;
	double z, y;
	char str[256];

	for (int x = 0; x < 196; x++)
	{
		fscanf(fitxategia, "%s", str);
		sscanf(str, "\"%lf\",\"%lf\",%i", &z, &y, &id);

		fwrite(&z, sizeof(double), 1, fitxategiadest);
		fwrite(&y, sizeof(double), 1, fitxategiadest);

	}

	fclose(fitxategia);
	fclose(fitxategiadest);
}

