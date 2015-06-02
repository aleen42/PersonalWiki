#include <stdio.h>
#define MAXSIZE 1000

int data[] = { 0, 2, 8, 5, 7, 9, 6, 4 };
int B[MAXSIZE];
int array_size = sizeof(data) / sizeof(int);


void printf_array(int A[], int array_size);
void COUNTSORT(int A[], int B[], int k, int array_size);


int main()
{
	printf_array(data, array_size);
	COUNTSORT(data, B, 9, array_size);
	printf_array(B, array_size);
	system("pause");
	return 0;
}

void printf_array(int A[], int array_size)
{
	for (int i = 0; i < array_size; i++)
		printf("%-3d", A[i]);
	printf("\n");
}

/* A[] to store data, B[] to store sorted data */
void COUNTSORT(int A[], int B[], int k, int array_size)
{
	int C[MAXSIZE];
	for (int i = 0; i <= k; i++)
		C[i] = 0;
	for (int j = 0; j <= array_size - 1; j++)
		C[A[j]]++;
	for (int i = 1; i <= k; i++)
		C[i] = C[i] + C[i - 1];
	
	for (int j = array_size - 1; j >= 0; j--)
	{
		B[C[A[j]] - 1] = A[j];
		C[A[j]]--;
	}
}