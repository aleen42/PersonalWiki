##Bubble Sort [Back](./../Sort.md)
- 冒泡排序 :每趟都把最大的沉到后。
- 时间复杂度：<img src="http://www.mathtran.org/cgi-bin/mathtran?D=2;tex=T(n)%20%3D%20O(n%5E2)">
- 空間複雜度：<img src="http://www.mathtran.org/cgi-bin/mathtran?D=2;tex=S(n)%20%3D%20O(1)">
- 稳定性 :稳定
- 适用情况 :数据,初始序列基本有初



```c
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
```

=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
