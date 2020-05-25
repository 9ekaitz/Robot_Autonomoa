#include "funtzioak.h"




void insertarNodo()
{

	Nodo*aux;
	Nodo*nuevo=(Nodo*)malloc(sizeof(Nodo));
	fflush(stdin);//mirar lo que hace
	printf("Inserte vertice");
	scanf("%c",&nuevo->dato);

	nuevo->siguiente=NULL;
	nuevo->adyacencia=NULL;

	if(inicio==NULL)
	{

		inicio=nuevo;
	}else
	{

		aux=inicio;

		while(aux->siguiente!=NULL)
		{
			aux=aux->siguiente;
		}
		aux->siguiente=nuevo;

	}
}
