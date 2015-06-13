#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define INFINITY 9999

void print_result(int d[]);
void DIJKSTRA(int G[][MAXSIZE], int d[], int source, int S[], int n, int pre[]);	//S set, 1 means existed
void print_matrix(int G[][MAXSIZE], int i, int j);
void print_path(int pre[], int source, int destination);

int main()
{
	int d[MAXSIZE];
	int S[MAXSIZE];
	int pre[MAXSIZE];	//Record the last point of current point 
	//int G[][MAXSIZE] = { { 0, 10, 3, 0, 0 }, {0, 0, 1, 2, 0 }, { 0, 4, 0, 8, 2 }, { 0, 0, 0, 0, 7 }, { 0, 0, 0, 9, 0 } };
	int G[][MAXSIZE] = { { 0, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 5, 0, 0, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 3, 0, 0, 0, 8, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 6, 8, 0, 0, 0, 0, 0, 0, 0 }, { 0, 3, 8, 0, 0, 0, 0, 3, 5, 0, 0, 0, 0, 0, 0, 0 }, { 0, 6, 7, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0 }, { 0, 0, 6, 0, 0, 0, 0, 0, 8, 4, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 6, 3, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0 }, { 0, 0, 0, 0, 5, 3, 8, 0, 0, 0, 0, 1, 2, 0, 0, 0 }, { 0, 0, 0, 0, 0, 3, 4, 0, 0, 0, 0, 3, 3, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3, 5, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 5, 2, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 6, 6, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 6, 0, 0, 4 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 2, 6, 0, 0, 3 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3 } };
	//print_matrix(G, 5, 5);
	int n = 16;
	DIJKSTRA(G, d, 0, S, n, pre);
	
	//for (int k = 1; k < n; k++)
	//{
	//	printf("%-4d", d[k]);
	//}
	int source = 0;
	int destination = 15;
	printf("%-4d:", d[destination]);
	print_path(pre, source, destination);
	printf("%-4d\n", destination);
	system("pause");
	return 0;
}

void print_matrix(int G[][MAXSIZE], int i, int j)
{
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			printf("%-3d", G[a][b]);
		}
		printf("\n");
	}
}

void print_result(int d[], int n)
{
	for (int i = 1; i <= n; i++)
	{
		printf("%-3d", d[i]);
	}
	printf("\n");
}

void print_path(int pre[],int source, int destination)
{
	if (pre[destination] != source)
		print_path(pre, source, pre[destination]);
	printf("%-4d->", pre[destination]);
}

void DIJKSTRA(int G[][MAXSIZE], int d[], int source, int S[], int n, int pre[])
{
	for (int i = 0; i < n; i++)
		S[i] = 0;

	d[source] = 0;
	S[source] = 1;

	int count = 1;	//number of s

	for (int i = 0; i < n; i++)
	{
		if (S[i] != 1)
			d[i] = INFINITY;
	}

	//UPDATE
	while (count != n)
	{
		int min = INFINITY + 1;
		int put;
		for (int i = 0; i < n; i++)
		{
			if (S[i] == 0)
				continue;
			else
			{
				for (int j = 0; j < n; j++)
				{
					if (S[j] == 1)
						continue;
					else
					{
						if (G[i][j] == 0)
							continue;
						else
						{
							if (d[j] == INFINITY || G[i][j] + d[i] <= d[j])
							{
								d[j] = G[i][j] + d[i];
								pre[j] = i;
								if (d[j] < min)
								{
									min = d[j];
									put = j;
								}
							}
						}
					}
				}
			}
		}
		if (min != INFINITY + 1)
			S[put] = 1;
		count++;
	}
}