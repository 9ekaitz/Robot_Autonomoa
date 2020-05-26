
#include <stdio.h>
#include <math.h>
typedef struct coordenadas {

	 double x;
	 double y;


} COORDENADAS;

int main(int argc, char* argv[]) {

	//crear extructura
	printf("esta haciendo cosas de matrices\n");

	int pixely=2;
	int pixelx=2;

	int x=1;
	//esto es lo que metes en la funcion
	double coordenaday=0;
	double coordenadax=0;



	int tamanodeimagenX=6616;
	int tamanodeimagenY=3765;

	double modulo_ab=0;
	double modulo_ac=0;

	double cachosy;
	double cachosx;

	COORDENADAS Upper_Left;//A
	COORDENADAS Lower_Left;//B
	COORDENADAS Upper_Right;//C


	//A
	Upper_Left.x=-220611.986;
	Upper_Left.y=5361961.764;

	//B
	Lower_Left.x=-220611.986;
	Lower_Left.y=5360844.969;




	//C
	Upper_Right.x=-218649.510;
	Upper_Right.y=5361961.764;




//creo los modulos para saber las distancias
modulo_ab=sqrt(pow(Upper_Left.x-Lower_Left.x,2)+pow(Upper_Left.y-Lower_Left.y,2));



modulo_ac=sqrt(pow(Upper_Left.x-Upper_Right.x,2)+pow(Upper_Left.y-Upper_Right.y,2));


//calculo cuntos tengo que sumar a la cordenada A para llegar a la cordenada C
cachosy=modulo_ab/tamanodeimagenY;
cachosx=modulo_ac/tamanodeimagenX;


//aqui podria estar mal

//saco la cordenada X e Y de pixeles a las de gps "EPSG:3857"

coordenaday=Upper_Left.y-(cachosy*pixely);

coordenadax=Upper_Left.x+(cachosx*pixelx);


    return 0;
}
