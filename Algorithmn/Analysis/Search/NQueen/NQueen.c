#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

int place(int k, int x[])
{
	int i = 1;
	while (i < k)
	{
		if (x[i] == x[k] || abs(x[i] - x[k]) == abs(i - k))
			return 0;
		i++;
	}
	return 1;
}

void N_QUEEN(int n, int x[])
{
	x[1] = 0;
	int k = 1;
	while (k > 0)
	{
		x[k] += 1;
		while (x[k] <= n && !place(k, x))
			x[k] += 1;
		if (x[k] <= n)
		{
			if (k == n)
				return;
			else
			{
				k++;
				x[k] = 0;
			}
		}
		else
			k--;
	}
}

int main()
{
	int x[MAXSIZE];
	int n = 8;
	N_QUEEN(n, x);
	for (int i = 1; i <= n; i++)
	{
		printf("%d\n", x[i]);
	}
	system("pause");
	return 0;
}