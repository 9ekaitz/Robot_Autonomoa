#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "matrizeasortu.h"
#include "matrizeakonprobatu.h"

int main()
{
	int aukera = 1;
	char str[128];

	while (aukera != 0)
	{
		printf("----------------------\n0. Irten\n1. Matrizea sortu\n2. Matrizea konprobatu\n3. Matrizea sinplifikatu\n----------------------\n");
		fgets(str, 128, stdin);
		sscanf(str, "%d", &aukera);

		switch(aukera)
		{
		case 1:
			matrizeaSortuExec();
			break;
		case 2:
			matrizeaKonprobatuExec();
			break;
		case 3:
			matrizeaSinplifikatu();
		}
	}


}

