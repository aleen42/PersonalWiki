#include<stdio.h>
void main()
{
	int num[64]
	int i, j, a = 0, temp;
	/* Load Data */
	while ((scanf("%d", &num[a]) != EOF)
	{
		a++;
	}
	/* Sort */
	for (i = 0; i < a; i++){
		for (j = 0; j < a - i; j++){
			if (num[j] > num[j + 1]){
				temp = num[j];
				nun[j] = num[j + 1];
				num[j + 1] = temp;
			}
		}
	}
	/* Output Data */
	for (i = 0; i < a; i++) {
		if (i < a - 1)
			printf("%d<", num[i]);
		else
			printf("%d", num[i]);
	}
}