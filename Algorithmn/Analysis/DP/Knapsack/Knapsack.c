#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000
#define MAXSIZE_ARRAY 200

typedef struct{
	int weight;
	int value;
	double value_of_weight;		//(double)value/weight
	double get;
}goods;

void exchange(goods g[], int q, int p)
{
	goods temp = g[q];
	g[q] = g[p];
	g[p] = temp;
}

int PARTITION(goods g[], int p, int q)
{
	double x = g[q].value_of_weight;		//pivot
	int i = p - 1;
	for (int j = p; j <= q - 1; j++)
	{
		if (g[j].value_of_weight >= x)
		{
			i++;
			exchange(g, i, j);
		}
	}
	exchange(g, i + 1, q);
	return i + 1;
}

void QUICKSORT(goods g[], int p, int q)
{
	if (p < q)
	{
		int m = PARTITION(g, p, q);
		QUICKSORT(g, p, m - 1);
		QUICKSORT(g, m + 1, q);
	}
}


void SORT_GOODS(goods g[], int size)
{
	QUICKSORT(g, 0, size - 1);
}

void GREEDY_KNAPSACK(goods g[], int size, int Capacity)
{
	SORT_GOODS(g, size);
	int c = Capacity;
	for (int i = 0; i < size;i++)
		g[i].get = 0;
	for (int i = 0; i < size; i++)
	{
		if (g[i].weight <= c)
		{
			c -= g[i].weight;
			g[i].get = 1;
		}
		else
		{
			g[i].get = (double)c / g[i].weight;
			break;
		}
	}
}

void DP_KNAPSACK(goods g[], int size, int Capacity, int c[][MAXSIZE_ARRAY])
{
	for (int i = 0; i < size; i++)
		g[i].get = 0;
	for (int i = 0; i <= Capacity; i++)
		c[0][i] = 0;
	for (int i = 1; i <= size; i++)
	{
		c[i][0] = 0;
		for (int j = 1; j <= Capacity; j++)
		{
			if (g[i - 1].weight <= j)
			{
				if (g[i - 1].value + c[i - 1][j - g[i - 1].weight] > c[i - 1][j])
					c[i][j] = g[i - 1].value + c[i - 1][j - g[i - 1].weight];		
				else
					c[i][j] = c[i - 1][j];		
			}
			else
				c[i][j] = c[i - 1][j];
		}
	}
}

int main()
{
	goods g[MAXSIZE];

	int size = 5;
	int capacity = 100;
	g[0].value = 20;
	g[0].weight = 10;

	g[1].value = 30;
	g[1].weight = 20;

	g[2].value = 65;
	g[2].weight = 30;

	g[3].value = 40;
	g[3].weight = 40;
	
	g[4].value = 60;
	g[4].weight = 50;

	//int capacity = 11;
	//g[0].value = 1;
	//g[0].weight = 1;

	//g[1].value = 6;
	//g[1].weight = 2;

	//g[2].value = 18;
	//g[2].weight = 5;

	//g[3].value = 22;
	//g[3].weight = 6;

	//g[4].value = 28;
	//g[4].weight = 7;

	/* caculate all the value of weight */
	for (int i = 0; i < size; i++)
		g[i].value_of_weight = (double)(g[i].value) / g[i].weight;


	//SORT_GOODS(g, size);
	/* greedy knapsack */
	printf("GREEDY_KNAPSACK\n");
	printf("value   weight  get\n");
	GREEDY_KNAPSACK(g, size, capacity);
	for (int i = 0; i < size; i++)
	{
		printf("%-7d %-7d %-7lf\n", g[i].value, g[i].weight, g[i].get);
	}


	int c[MAXSIZE_ARRAY][MAXSIZE_ARRAY];
	/* 01 knapsack */
	printf("01 KNAPSACK\n");
	printf("value   weight  get\n");
	DP_KNAPSACK(g, size, capacity, c);
	for (int i = 0; i < size; i++)
	{
		printf("%-7d %-7d %-7lf\n", g[i].value, g[i].weight, g[i].get);
	}
		
	//for (int i = 0; i <= size; i++)
	//{
	//	for (int j = capacity; j <= capacity; j++)
	//		printf("%-4d", c[i][j]);
	//	printf("\n");
	//}
	printf("%-4d\n", c[size][capacity]);
	

	system("pause");
	return 0;
}