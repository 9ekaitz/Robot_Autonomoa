/*
 * funtzioak.c
 *
 *  Created on: 20 may. 2020
 *      Author: gorkalertxundi
 */
#include "SDL2/SDL.h"
#include <stdio.h>
#include <float.h> //para FLT_MAX eta INT_MAX

#define MAXNODOAK 100  //SISTEMAREN NODO MAXIMOAK
#define DEFINITUGABEA -1

int N;
float bidea[MAXNODOAK][MAXNODOAK];
float minimo[MAXNODOAK];
int aurrekoa[MAXNODOAK];
int bisitatua[MAXNODOAK];

void dijkstra (int A, int B)
{
	int nodoa;
	minimo[A] = 0.0;
	while (minimoNodoNoVisitado(&nodoa))
	{
		if (minimo[nodoa] == FLT_MAX) //Infinito para los amigos
		{
			return; //Urrengo bideak akzesu gabe daude (nodo honetatik)
		}
		bisitatua[nodoa] = TRUE;
		for (int i = 0; i < N; i++)
		{
			if(!bisitatua[i] && distantzia[nodoa][i] < 1.0)
			{
				float posibleMin = minimo[nodoa] + distantzia[nodoa][i];

				if (posibleMin < minimo[i])
				{
					minimo[i] = posibleMin;
					aurrekoa[i] = nodoa;
				}
			}
		}
	}

}

int minimoNodoNoVisitado (int * nodoa)
{
	int aukeratua = -1;
	for (int i = 0; i < N; ++i)
	{
		if (!bisitatua[i] && (minimo[i] < minimo[aukeratua]) || aukeratua == -1)
		{
			aukeratua = i;
		}
		*nodoa = aukeratua;
		return aukeratua != -1;
	}
}

void biderikMotzena(int A, int B) //A = hasiera B = amaiera
{
	if (A != B)
	{
		biderikMotzena(A, aurrekoa[B]);
		printf(", ");
	}
	printf("%i", B);
}

