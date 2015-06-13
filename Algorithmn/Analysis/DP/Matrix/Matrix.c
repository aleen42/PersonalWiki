#include <stdio.h>
#include <stdlib.h>
#define INFINITY 999999999
#define MAXSIZE 100
#define matrix_num 6
#define case1_num 4
#define case2_num 4
#define case3_num 5
#define case4_num 6

void MATRIX_CHAIN_ORDER(int m[][MAXSIZE], int s[][MAXSIZE], int p[], int p_array_size);
void PRINT_OPTIMAL_PARENS(int s[][MAXSIZE], int i, int j);


int main()
{
	//int p[matrix_num + 1] = { 30, 35, 15, 5, 10, 20, 25 };
	//int m[matrix_num + 1][matrix_num + 1], s[matrix_num + 1][matrix_num + 1];
	//MATRIX_CHAIN_ORDER(m, s, p, matrix_num + 1);
	//PRINT_OPTIMAL_PARENS(s, 1, matrix_num);
	//printf("\n");
	//printf("%d\n", m[1][6]);

	/* case 1 */
	int m[MAXSIZE][MAXSIZE], s[MAXSIZE][MAXSIZE];
	int case1[case1_num + 1] = { 3, 5, 2, 1, 10 };
	MATRIX_CHAIN_ORDER(m, s, case1, case1_num + 1);
	PRINT_OPTIMAL_PARENS(s, 1, case1_num);
	printf("\n");

	/* case 2 */
	int case2[case2_num + 1] = { 2, 7, 3, 6, 10 };
	MATRIX_CHAIN_ORDER(m, s, case2, case2_num + 1);
	PRINT_OPTIMAL_PARENS(s, 1, case2_num);
	printf("\n");

	/* case 3 */
	int case3[case3_num + 1] = { 10, 3, 15, 12, 7, 2 };
	MATRIX_CHAIN_ORDER(m, s, case3, case3_num + 1);
	PRINT_OPTIMAL_PARENS(s, 1, case3_num);
	printf("\n");

	/* case 4 */
	int case4[case4_num + 1] = { 5, 10, 3, 12, 5, 50, 6 };
	MATRIX_CHAIN_ORDER(m, s, case4, case4_num + 1);
	PRINT_OPTIMAL_PARENS(s, 1, case4_num);
	printf("\n");
	for (int i = 0; i <= case4_num; i++)
	{
		for (int j = 0; j <= case4_num; j++)
		{
			printf("%-15d", s[i][j]);
		}
		printf("\n");
	}
	printf("\n");


	system("pause");
	return 0;
}

void MATRIX_CHAIN_ORDER(int m[][MAXSIZE], int s[][MAXSIZE], int p[], int p_array_size)
{
	int n = p_array_size - 1;
	for (int i = 1; i <= n; i++)
		m[i][i] = 0;				//矩阵本身相乘并没有计算次数
	for (int l = 2; l <= n; l++)
	{
		for (int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;
			m[i][j] = INFINITY;
			for (int k = i; k <= j - 1; k++)
			{
				int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	
}

void PRINT_OPTIMAL_PARENS(int s[][MAXSIZE], int i, int j)
{
	if (i == j)
		printf("A%d ", i);
	else
	{
		printf("(");
		PRINT_OPTIMAL_PARENS(s, i, s[i][j]);
		PRINT_OPTIMAL_PARENS(s, s[i][j] + 1, j);
		printf(")");
	}
}