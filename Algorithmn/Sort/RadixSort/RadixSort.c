#include <stdio.h>

int data[] = { 329, 457, 657, 839, 436, 720, 355 };
int array_size = sizeof(data) / sizeof(int);

void printf_array(int A[], int array_size);
void RADIXSORT(int A[], int d);


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

void RADIXSORT(int A[], int d)
{
	for (int i = 1; i <= d; i++);
		//use a stable sort to sort array A on digit i
}