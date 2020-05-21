#include <stdio.h>
#include <limits.h>
//Ekaitz Dijkstra

#define KOP 8

int main()
{
	int infinite = INT_MAX;
int grafiko[KOP][KOP] = {
{0,10,3,8,infinite,infinite,infinite,infinite},		//A
{10,0,8,infinite,6,infinite,infinite,infinite},		//B
{3,8,0,4,infinite,9,infinite,infinite},				//C
{8,infinite,4,0,infinite,infinite,7,infinite},		//D
{infinite,6,infinite,infinite,0,3,infinite,11},		//E
{infinite,infinite,9,infinite,3,0,1,8},				//F
{infinite,infinite,infinite,7,infinite,1,0,5},		//G
{infinite,infinite,infinite,infinite,11,8,5,0}		//H
};

dijkstra(grafiko, start, end, path);

return  0;
}
