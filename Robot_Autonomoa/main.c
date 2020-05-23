#include <stdio.h>
#include <limits.h>
//Ekaitz Dijkstra

#define KOP 8

typedef struct path{
	int cost;
	int vertex[KOP];
	int len;
}PATH;

PATH dijkstra(int matrix[KOP][KOP], int start, int end);

void copyPath(int *destVertex, int *destLen, int *srcVertex, int srcLen);

int main()
{
	int infinite = INT_MAX, start = 0, end = 4;
	PATH path;
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

	path = dijkstra(grafiko, start, end);

return  0;
}

PATH dijkstra(int matrix[KOP][KOP], int start, int end)
{
	PATH map[KOP];
	int infinite = INT_MAX;
	int visited[KOP];
	int min, pos;

	for (int i = 0; i < KOP+1; i++)
	{
		map[i].cost = infinite;
		visited[i] = 0;
	}

	map[start].cost = 0;
	map[start].vertex[0] = start;
	map[start].len = 1;
	visited[start] = 1;
	pos = start;

	while (!visited[end])
	{
		min = KOP;
		for (int j = 0; j < KOP; j++)
		{
			if (!visited[j] && (matrix[pos][j] + map[pos].cost) < map[min].cost)
			{
				min = j;
			}
		}
		for (int j = 0; j < KOP; j++)
		{
			if (!visited[j] && map[min].cost + matrix[min][j] < map[j].cost)
			{
				copyPath(map[j].vertex, &map[j].len, map[min].vertex, map[min].len);
				map[j].vertex[map[j].len] = j;
				map[j].len++;
			}
		}
		visited[min] = 1;
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
