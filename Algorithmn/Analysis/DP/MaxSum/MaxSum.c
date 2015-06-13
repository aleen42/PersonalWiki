#include <stdio.h>
#include <stdlib.h>
#define reserve -9999
#define MAXSIZE 100
int BetterMaxSum(int n, int a, int *besti, int *bestj);

int main()
{
	int besti, bestj;
	int data[] = { reserve, -2, 11, -4, 13, -5, -2 };
	printf("from %-3d to %-3d, sum is %-3d\n", besti, bestj, BetterMaxSum(6, data, &besti, &bestj));
	printf("from %-3d to %-3d, sum is %-3d\n", besti, bestj, DPMaxSum(6, data, &besti, &bestj));
	system("pause");
	return 0;
}

int BetterMaxSum(int size, int data[], int *besti, int *bestj)
{
	int sum = -1;
	for (int i = 1; i <= size; ++i)
	{
		int thissum = 0;
		for (int j = i; j <= size; ++j)
		{
			thissum += data[j];
			if (thissum > sum)
			{
				sum = thissum;
				*besti = i, *bestj = j;
			}
		}
	}
	return sum;
}

int DPMaxSum(int n, int data[], int *besti, int *bestj)
{
	int sum = data[1]; 
	int b[MAXSIZE];
	b[1] = data[1];
	for (int i = 2; i <= n; ++i)
	{
		if (b[i - 1] > 0)
			b[i] = b[i - 1] + data[i];
		else
		{
			b[i] = data[i];
			*besti = i;
		}
		if (b[i] > sum)
		{
			sum = b[i];
			*bestj = i;
		}
			
	}
	return sum;
}

