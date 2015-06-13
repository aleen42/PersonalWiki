#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define INFINITY 9999

void FLOYD_WARSHALL(int G[][MAXSIZE], int n, int C[][MAXSIZE],int pre[][MAXSIZE])
{
	/* C0 */
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			C[i][j] = G[i][j];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (G[i][j] != INFINITY && i != j)
				pre[i][j] = i;
			else
				pre[i][j] = INFINITY;
		}
	}
		
			

	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (C[i][j] > C[i][k] + C[k][j] && C[i][k] != INFINITY && C[k][j] != INFINITY)
				{
					C[i][j] = C[i][k] + C[k][j];
					pre[i][j] = k;
				}
			}
		}
	}
		
			
				
}

void print_path(int pre[][MAXSIZE], int source, int destination)
{
	if (pre[source][destination] == INFINITY || source == destination)
	{
		printf("cannot arrive!\n");
		return;
	}
	if (pre[source][destination] != source)
		print_path(pre, source, pre[source][destination]);
	printf("%-4c->", pre[source][destination] + 65);
}


int main()
{
	int C[MAXSIZE][MAXSIZE];
	int pre[MAXSIZE][MAXSIZE];
	int G[][MAXSIZE] = { { 0, -1, 3, INFINITY, INFINITY }, { INFINITY, 0, 3, 2, 2 }, { INFINITY, INFINITY, 0, INFINITY, INFINITY }, { INFINITY, 1, 5, 0, INFINITY }, { INFINITY, INFINITY, INFINITY, -3, 0 } };
	//int G[][MAXSIZE] = { { 0, 4, 11 }, { 6, 0, 2 }, { 3, INFINITY, 0 } };
	int n = 5;

	FLOYD_WARSHALL(G, n, C, pre);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%-10d", C[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	print_path(pre, 0, 2);
	printf("%c  total_len: %d\n", 2 + 65, C[0][2]);
	printf("\n");
	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = 0; j < n; j++)
	//	{
	//		printf("%-10d", pre[i][j]);
	//	}
	//	printf("\n");
	//}
	
			
	system("pause");
	return 0;
}