#include <stdio.h>
#include <math.h>

#define IMG_HEIGHT 2912
#define IMG_WIDTH 6873

typedef struct koord{
		double x, y;
	}KOORD;

	typedef struct PixelKoord{
			int x, y;
		}PIXELKOORD;

	PIXELKOORD coordToPixel(KOORD point);

int main() {
	KOORD point;

	coordToPixel(point);

    return 0;
}

PIXELKOORD coordToPixel(KOORD point)
{
	double gap_x, gap_y, width_c, height_c;

	KOORD Upper_Left;//A
	KOORD Lower_Left;//B
	KOORD Upper_Right;//c
	PIXELKOORD result;

	//A
	Upper_Left.x=-1.9802276;
	Upper_Left.y=43.3271173;

	//B
	Lower_Left.x=-1.9802276;
	Lower_Left.y=43.3206861;

	//C
	Upper_Right.x=-1.9650484;
	Upper_Right.y=43.3271173;

	//creo los modulos para saber las distancias
	width_c = sqrt(pow(Upper_Left.x-Upper_Right.x,2)+pow(Upper_Left.y-Upper_Right.y,2));
	height_c = sqrt(pow(Upper_Left.x-Lower_Left.x,2)+pow(Upper_Left.y-Lower_Left.y,2));

	//calculo cuntos tengo que sumar a la cordenada A para llegar a la cordenada C
	gap_x = width_c/IMG_WIDTH;
	gap_y = height_c/IMG_HEIGHT;

	result.x = (point.x - Upper_Left.x) / gap_x;
	result.y = ((point.y - Upper_Left.y)/-gap_y);	//+1 eginez pixela hobeta

	return result;
}
