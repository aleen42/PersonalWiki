#include <stdio.h>

int data[] = { 8, 5, 7, 9, 6, 4 };
int array_size = sizeof(data) / sizeof(int);

void printf_array(int A[], int array_size);
void INSERTSORT(int A[],int array_size);

int main()
{
	printf_array(data,array_size);
	INSERTSORT(data, array_size);
	printf_array(data,array_size);
	system("pause");
	return 0;
}

void printf_array(int A[], int array_size)
{
	for (int i = 0; i < array_size; i++)
		printf("%-3d", A[i]);
	printf("\n");
}

void INSERTSORT(int A[], int array_size)
{
	int j;
	for (j = 1; j <= array_size - 1; j++)
	{
		int key = A[j];
		int i = j - 1;
		while (i >= 0 && A[i] > key)
		{
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}
}