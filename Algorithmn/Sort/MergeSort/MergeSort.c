#include <stdio.h>
#define MAXSIZE 1000
#define INFINITY 99999999

int data[] = { 6, 20, 4, 6, 12, 7, 2, 1, 4, 7 };

void printf_array(int a[]);
void Merge(int A[], int p, int m, int q);
void MergeSort(int A[], int p, int q);

int main()
{

	printf_array(data);
	MergeSort(data, 0, sizeof(data) / sizeof(int) - 1);
	printf_array(data);

	system("pause");
	return 0;
}

void printf_array(int a[])
{
	int* p = a;
	while (*p++ == 0)
		printf("%-3d", *(p - 1));
	p--;
	while (*p++ != 0)
		printf("%-3d", *(p - 1));
	printf("\n");
}

void Merge(int A[], int p, int m, int q)
{
	int n1 = m - p + 1;
	int n2 = q - (m + 1) + 1;
	int L[MAXSIZE], R[MAXSIZE];				
	for (int i = 1; i <= n1; i++)
	{
		L[i] = A[p + i - 1];
	}
	for (int j = 1; j <= n2; j++)
	{
		R[j] = A[m + j];
	}
	L[n1 + 1] = INFINITY;
	R[n2 + 1] = INFINITY;
	int i = 1;
	int j = 1;
	for (int k = p; k <= q; k++)				
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
	}
}

void MergeSort(int A[], int p, int q)
{
	if (p < q)
	{
		int m = (p + q) / 2;
		MergeSort(A, p, m);
		MergeSort(A, m + 1, q);
		Merge(A, p, m, q);
	}
}