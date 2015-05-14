#include <stdio.h>
#define MAXSIZE 10000


void QUICKSORT(int A[], int p, int q);
int PARTITION(int A[], int p, int q);
void exchange(int A[], int q, int p);
void printf_array(int A[], int array_size);
void data_Initilize(int n);



int data[] = { 3, 6, 7, 1, 2, 5, 8, 4 };
int array_size = sizeof(data) / sizeof(int);


int max_data[] = { 3, 6, 7, 1, 2, 5, 8, 4 };
int max_array_size = sizeof(max_data) / sizeof(int);
int min_data[] = { 1, 1, 1, 1, 1, 1, 1, 1 };
int min_array_size = sizeof(min_data) / sizeof(int);

//int data[MAXSIZE];
int count;


int main()
{
	//int n = 1;
	printf("%-4s compares\n\n", "n");
	//for (; n <= 100; n++)
	//{
	//	data_Initilize(n);
	//	count = 0;
	//	QUICKSORT(data, 0, n - 1);
	//	printf("%-4d %d\n", n, count);
	//}

	count = 0;
	QUICKSORT(max_data, 0, max_array_size - 1);
	printf("%-4d %d\n", max_array_size, count);

	count = 0;
	QUICKSORT(min_data, 0, min_array_size - 1);
	printf("%-4d %d\n", min_array_size, count);

	//QUICKSORT(data, 0, array_size - 1);


	int m = PARTITION(data, 0, array_size - 1);
	PARTITION(data, 0, m - 1);
	PARTITION(data, m + 1, array_size - 1);
	printf_array(data, array_size);

	system("pause");
	return 0;
}

void data_Initilize(int n)
{
	for (int i = 0; i < n; i++)
		data[i] = 1;				//n same elements
}

void QUICKSORT(int A[], int p, int q)
{
	if (p < q)
	{
		int m = PARTITION(A, p, q);
		QUICKSORT(A, p, m - 1);
		QUICKSORT(A, m + 1, q);
	}
}

int PARTITION(int A[], int p, int q)
{
	int x = A[q];		//pivot
	int i = p - 1;
	for (int j = p; j <= q - 1; j++)
	{	
		count++;
		if (A[j] <= x)
		{
			i++;
			exchange(A, i, j);
		}
	}
	exchange(A, i + 1, q);
	return i + 1;
}

void exchange(int A[], int q, int p)
{
	int temp = A[q];
	A[q] = A[p];
	A[p] = temp;
}

void printf_array(int A[], int array_size)
{
	for (int i = 0; i < array_size; i++)
		printf("%-4d", A[i]);
	printf("\n");
}