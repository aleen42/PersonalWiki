#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define INFINITY 9999



void BELLMAN_FORD(int G[][MAXSIZE], int d[], int source, int n, int pre[])
{
	d[source] = 0;
	for (int i = 0; i < n; i++)
	{
		if (i == source)
			continue;
		d[i] = INFINITY;
	}
	int i;
	for (int times = 0; times < n - 1; times++)
	{
		for (i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (G[i][j] != 0 && (G[i][j] + d[i] < d[j] || d[j] == INFINITY))
				{
					d[j] = G[i][j] + d[i];
					pre[j] = i;
				}
			}
		}
	}
	for (i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (G[i][j] != 0 && (G[i][j] + d[i] < d[j] || d[j] == INFINITY))
			{
				printf("a negative-weight cycle exists\n");
				system("pause");
				return 0;
			}
		}
	}

}

void print_path(int pre[], int source, int destination)
{
	if (pre[destination] != source)
		print_path(pre, source, pre[destination]);
	printf("%-4c->", pre[destination] + 65);
}

int main()
{
	int d[MAXSIZE];
	int pre[MAXSIZE];	//Record the last point of current point 
	//int G[][MAXSIZE] = { { 0, 10, 3, 0, 0 }, {0, 0, 1, 2, 0 }, { 0, 4, 0, 8, 2 }, { 0, 0, 0, 0, 7 }, { 0, 0, 0, 9, 0 } };
	int G[][MAXSIZE] = { { 0, -1, 3, 0, 0 }, { 0, 0, 3, 2, 2 }, { 0, 0, 0, 0, 0 }, { 0, 1, 5, 0, 0 }, { 0, 0, 0, -3, 0 } };

	int n = 5;
	BELLMAN_FORD(G, d, 0, n, pre);

	//for (int i = 0; i < n;i++)
	//	printf("%-4d", d[i]);
	//printf("\n");

	for (int i = 0; i < n; i++)
	{
		if (i == 0)
			continue;
		print_path(pre, 0, i);
		printf("%c  total_len: %d\n", i + 65, d[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}