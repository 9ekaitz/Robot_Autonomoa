#include <stdio.h>
#include <limits.h>
//Ekaitz Dijkstra

#define KOP 8 //nodos

typedef struct path{
	int cost;
	int vertex[KOP];
	int len;
}PATH;

PATH dijkstra(uint matrix[KOP][KOP], int start, int end);

void copyPath(int *destVertex, int *destLen, int *srcVertex, int srcLen);

int main()
{

	int infinite = INT_MAX, start = 0, end = 7;

	PATH path;
uint grafiko[KOP][KOP] = {
		{infinite,10,3,8,infinite,infinite,infinite,infinite},			//A
		{10,infinite,8,infinite,6,infinite,infinite,infinite},			//B
		{3,8,infinite,4,infinite,9,infinite,infinite},					//C
		{8,infinite,4,infinite,infinite,infinite,7,infinite},			//D
		{infinite,6,infinite,infinite,infinite,3,infinite,11},			//E
		{infinite,infinite,9,infinite,3,infinite,1,8},					//F
		{infinite,infinite,infinite,7,infinite,1,infinite,5},			//G
		{infinite,infinite,infinite,infinite,11,8,5,infinite}			//H
};

	path = dijkstra(grafiko, start, end);

return  0;
}

PATH dijkstra(uint matrix[KOP][KOP], int start, int end)
{
	PATH map[KOP];
	int infinite = INT_MAX;
	int visited[KOP];
	int min, pos, min_pos;

	//iniciar todo ha 0
	for (int i = 0; i < KOP; i++)
	{
		map[i].cost = infinite;
		map[i].len = 0;
		visited[i] = 0;
		if (matrix[start][i] < infinite)
		{
			map[i].cost = matrix[start][i];
			map[i].vertex[map[i].len] = start;
			map[i].len++;
		}
	}

	map[start].cost = 0;
	map[start].vertex[0] = start;
	map[start].len = 1;
	visited[start] = 1;
	while (!visited[end])
	{
		min = start;
		min_pos = start;
		for (pos = 0; pos < KOP; pos++)
		{
			if (visited[pos])
			{
				//j es la letra a la que estas mirando
				//mira la siguiente ruta mas pequeña
				for (int j = 0; j < KOP; j++)
				{
					if (!visited[j] && (matrix[pos][j] + map[pos].cost) < (matrix[min_pos][min] + map[min_pos].cost))
					{
						min = j;
						min_pos = pos;
					}
				}
			}
		}
		//comprueba si la nueva ruta es mas pequeña para ir a un nodo que la que ya teniamos
		for (int i = 0; i < KOP; i++)
		{
			printf("%d\n", matrix[min][i] + map[min].cost);
			if (matrix[min][i] + map[min].cost < map[i].cost)
			{
				map[i].cost = matrix[min][i] + map[min].cost;
				copyPath(map[i].vertex, &map[i].len, map[min].vertex, map[min].len);
				map[i].vertex[map[i].len] = min;
				map[i].len++;
			}
		}
		visited[min] = 1;//marcas el nodo como visitado
	}
	return map[end];
}

void copyPath(int *destVertex, int *destLen, int *srcVertex, int srcLen)
{
	for (int i = 0; i < srcLen; i++)
	{
		*(destVertex + i) = *(srcVertex + i);
	}
	*destLen = srcLen;
}
