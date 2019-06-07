#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void displayPath(int** path, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", path[i][j]);
		}
		printf("\n");
	}
}

int findPath(int  ** maze,int** visited, int m,int n,int ratx,int raty,int chx,int chy)
{
	if (ratx < m &&ratx >= 0 && raty >= 0 && raty < n && maze[ratx][raty] != 0 && visited[ratx][raty]==0)
	{
		if (ratx == chx&& raty == chy)
		{
			visited[ratx][raty] = 1;
			return 1;
		}
			visited[ratx][raty] = 1;
			if (findPath(maze, visited, m, n, ratx, raty + 1, chx, chy))
				return 1;
			if (findPath(maze, visited, m, n, ratx + 1, raty, chx, chy))
				return 1;
			if (findPath(maze, visited, m, n, ratx, raty - 1, chx, chy))
				return 1;
			
			if (findPath(maze, visited, m, n, ratx - 1, raty, chx, chy))
				return 1;
			visited[ratx][raty] = 0;
			return 0;
	}
	return 0;
}

int main()
{
	int m = 3, n = 3;
	int** maze = (int**)malloc(m * sizeof(int*));
	int** visited = (int**)malloc(n* sizeof(int*));
	for (int index = 0; index<m; ++index)
	{
		maze[index] = (int*)malloc(n * sizeof(int));
	}
	for (int index = 0; index < m; ++index)
	{
		visited[index] = (int*)malloc(n * sizeof(int));
	}
	//int(*maze)[3];
	//maze = (int(*)[3])malloc(sizeof(*maze)*m);
	//int(*visited)[3];
	//visited = (int(*)[3])malloc(sizeof(*visited)*m);
	//memset(maze, 1, m*n*sizeof(int));
	//maze[1][1] = 0;
	//memset(visited, 0, m*n*sizeof(int));
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			maze[i][j] = 1;
	maze[1][1] = 0;
	maze[2][1] = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			visited[i][j] = 0;
	/*for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", visited[i][j]);
		}
		printf("\n");
	}*/
	/*for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}*/
	int ratx = 1, raty = 0;
	int chx = 1, chy = 2;
	findPath((int**)maze,(int**)visited,m,n,ratx,raty,chx,chy);
	displayPath((int**)visited, m, n);
	getchar();
}