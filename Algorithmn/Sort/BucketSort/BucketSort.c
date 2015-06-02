#include <stdio.h>

int data[] = { 0.74, 0.14, 0.5, 0.8, 0.64, 0.22, 0.53 };
int array_size = sizeof(data) / sizeof(int);

void printf_array(int A[], int array_size);
void BUCKETSORT(int A[], int d);


int main()
{
	printf_array(data, array_size);

	system("pause");
	return 0;
}

void printf_array(int A[], int array_size)
{
	for (int i = 0; i < array_size; i++)
		printf("%-3d", A[i]);
	printf("\n");
}

/* [0,1) */
void BUCKETSORT(int A[], int array_size)
{
	int n = array_size;
	for (int i = 1; i <= n; i++)
		insert_list(B[n*A[i]], A[i]);
	for (int i = 0; i <= n - 1; i++)
		INSERTIONSORT(B[i], B[i].array_size);
}