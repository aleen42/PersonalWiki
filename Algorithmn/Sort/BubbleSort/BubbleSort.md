##Bubble Sort [Back](./../Sort.md)
'#include<stdio.h>
void main()
{
	int num[64]
		int i, j, a = 0, temp;
	while ((scanf("%d", &num[a]) != EOF)
	{
		a++;
	}
	for (i = 0; i<a; i++){
		for (j = 0; j<a - i; j++){
			if (num[j]>num[j + 1]){
				temp = num[j];
				nun[j] = num[j + 1];
				num[j + 1] = temp;
			}
		}
	}
	for (i = 0; i<a; i++) {
		if (i<a - 1)
			printf("%d<", num[i]);
		else
			printf("%d", num[i]);
	}
}'

=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
