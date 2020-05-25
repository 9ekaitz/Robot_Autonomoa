
#include <stdio.h>
#include <stdlib.h>

#define Nodo struct nodo
#define Arista struct arista
#define Lista struct lista



Nodo{

	char dato;
	Nodo*siguiente;
	Arista* adyacencia;
	//int visitado; //0 no 1 si
	//int terminado;
	////int monto; //coste total
	////char anterior; //letra del nodo anterior

};


Arista{
	Nodo*vrt;
	Arista*siguiente;
	////int peso;
};

Lista{
	Nodo*dato;
	Lista*siguiente;

};



void insertarNodo();












