#include <stdio.h>
#define MAXSIZE 1000
#define LOW_INFINITY -9999999
int data[] = { 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };
int array_size = sizeof(data) / sizeof(int);
int heap_size = sizeof(data) / sizeof(int);

void printf_array(int A[], int array_size);
int PARENT(int i);
int LEFT(int i);
int RIGHT(int i);
void exchange(int A[], int q, int p);
void BUILD_MAX_HEAP(int A[], int heap_size);
void MAX_HEAPIFY(int A[], int heap_size, int i);
void HEAPSORT(int A[], int* heap_size);
void MAXIMUM(int A[]);
int HEAP_EXTRACT_MAX(int A[], int *heap_size);
void HEAP_INCREASE_KEY(int A[], int i, int key);
void MAX_HEAP_INSERT(int A[], int* heap_size, int key);


int main()
{
	BUILD_MAX_HEAP(data, heap_size);
	
	//HEAP_INCREASE_KEY(data, 0, 13);
	printf_array(data, array_size);
	//int max = HEAP_EXTRACT_MAX(data, &heap_size);
	//printf("%d\n", max);
	//MAX_HEAP_INSERT(data, &heap_size, 20);
	system("pause");
	return 0;
}


void printf_array(int A[], int array_size)
{
	for (int i = 0; i < array_size; i++)
		printf("%-4d", A[i]);
	printf("\n");
}

int LEFT(int i)
{
	return 2 * i + 1;
}

int RIGHT(int i)
{
	return 2 * i + 2;
}

int PARENT(int i)
{
	if (i % 2 == 0)
		return i / 2 - 1;
	else
		return i / 2;
}

void exchange(int A[], int q, int p)
{
	int temp = A[q];
	A[q] = A[p];
	A[p] = temp;
}

void MAX_HEAPIFY(int A[], int heap_size, int i)
{
	int largest;
	int l = LEFT(i);
	int r = RIGHT(i);
	if (l < heap_size && A[l] > A[i])
		largest = l;
	else
		largest = i;

	if (r < heap_size && A[r] > A[largest])
		largest = r;
	if (largest != i)
	{
		exchange(A, i, largest);
		MAX_HEAPIFY(A, heap_size, largest);
	}
}

void BUILD_MAX_HEAP(int A[], int heap_size)
{
	for (int i = heap_size / 2 - 1; i >= 0; i--)
		MAX_HEAPIFY(A, heap_size, i);
}

void HEAPSORT(int A[], int* heap_size)
{
	BUILD_MAX_HEAP(A,*heap_size);
	
	for (int i = *heap_size - 1; i > 0; i--)
	{
		exchange(A, 0, i);
		*heap_size = *heap_size - 1;
		MAX_HEAPIFY(A, *heap_size, 0);
	}
}

void MAXIMUM(int A[])
{
	return A[0];
}

int HEAP_EXTRACT_MAX(int A[],int *heap_size)
{
	if (*heap_size < 1)
	{
		printf("heap underflow\n");
		return -1;
	}
	int max = A[0];
	A[0] = A[*heap_size - 1];
	*heap_size = *heap_size - 1;
	MAX_HEAPIFY(A, *heap_size, 0);
	return max;
}

void HEAP_INCREASE_KEY(int A[], int i, int key)
{
	if (key < A[i])
	{
		printf("new key is small than current key\n");
		return -1;
	}
	A[i] = key;
	while (i > 0 && A[PARENT(i)] < A[i])
	{
		exchange(A, i, PARENT(i));
		i = PARENT(i);
	}
}

void MAX_HEAP_INSERT(int A[], int* heap_size, int key)				//use with more larger array
{
	*heap_size = *heap_size + 1;
	A[*heap_size] = LOW_INFINITY;
	HEAP_INCREASE_KEY(A, *heap_size - 1, key);
}