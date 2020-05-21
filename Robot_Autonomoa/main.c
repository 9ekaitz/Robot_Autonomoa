#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_STR 128

//Gorka

typedef enum BOOLEANOA {FALSE, TRUE};

typedef struct Nodoa{
	char izena;
	int bisitatua;
	int amaitua;
	int bide_kant;
	char aurrekoa;
	struct Ertza* gertuena;
	struct Nodoa* ptrHurrengoa;
}NODOA;

typedef struct Ertza{
	struct Nodoa* ertza;
	int pisua;
	struct Ertza* ptrHurrengoa;
}ERTZA;

typedef struct Zerrenda{
	struct Nodoa* izena;
	struct Zerrenda* ptrHurrengoa;
}ZERRENDA;


int main(int argc, char* argv[])
{
	NODOA* nodohasiera = NULL;
	ZERRENDA* zerrendahasiera = NULL;
	ZERRENDA* zerrendaamaiera = NULL;

    return 0;
}
void ErpinaHasieratu(NODOA* berria)
{
	berria->ptrHurrengoa = NULL;
	berria->gertuena = NULL;
	berria->bisitatua = FALSE;
	berria->amaitua = FALSE;
	berria->bide_kant = -1;
	berria->aurrekoa = 0;
}
void NodoanSartu(NODOA* nodohasiera)
{
	NODOA* aux;
	NODOA* berria = (NODOA*)malloc(sizeof(NODOA));
	char str[MAX_STR];

	printf("Sartu mapako puntuaren izena: ");
	fgets(str, 128, stdin);
	sscanf(str, "%c", &berria->izena);

	ErpinaHasieratu(&berria);

	if (nodohasiera == NULL)
	{
		nodohasiera = berria;
	}
	else {
		aux = berria;
		while(aux->ptrHurrengoa != NULL)
		{
			aux = aux->ptrHurrengoa;
		}
		aux->ptrHurrengoa = berria;
	}

}

void ErtzaSartu(NODOA* nodohasiera)
{
	char A, B, str[MAX_STR];
	NODOA* aux = nodohasiera;
	NODOA* aux2 = nodohasiera;
	ERTZA* berria = (ERTZA*)malloc(sizeof(ERTZA));

	berria->ptrHurrengoa = NULL;

	if(nodohasiera == NULL)
	{
		printf("Error: Grafoa utsik dago!\n");
	}

	printf("Sartu ertzaren hasiera puntua: ");
	fgets(str, MAX_STR, stdin);
	sscnaf(str, "%c", &A);
	printf("Sartu ertzaren amaiera puntua: ");
	fgets(str, MAX_STR, stdin);
	sscnaf(str, "%c", &B);

	printf("Sartu ertzaren pisua: ");
	fgets(str, MAX_STR, stdin);
	sscanf(str, "%d", &berria->pisua);

	//Konprobatu behar ea ondo dagoen
	//AMAITZEKO
}

void Dijkstra(NODOA* nodohasiera)
{
	NODOA* aux = nodohasiera;
	char A, B;

	while (aux != NULL)
	{
		if(aux->izena == A)
		{
			aux->amaitua = TRUE;
			aux->bide_kant = 0;
			break;
		}
		aux = aux->ptrHurrengoa;
	}
	if (aux == NULL)
	{
		printf("Error: Erpina ez da aurkitu!\n");
		return;
	}
	while (aux != NULL)
	{
		ERTZA* aux2 = aux->gertuena;
		while (aux2 != NULL)
		{
			if((aux2->ertza->bide_kant == -1) || (aux->bide_kant + aux2->pisua < aux2->ertza->bide_kant) ) //Ertz hau ez bada horaindik bisitatu edo
			{

			}
		}
	}
}
