#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100
//#define x_size 7
//#define y_size 6


enum DIRECTION
{
	TOP,
	LEFT,
	TOP_LEFT
};

void printf_array(int c[][MAXSIZE], int i, int j);
void LCS_LENGTH(char x[], char y[], int x_array_size, int y_array_size, int c[][MAXSIZE], int b[][MAXSIZE]);
void PRINT_LCS(int b[][MAXSIZE], char x[], int i, int j);

int main()
{
	//char x[x_size + 1] = { '-', 'A', 'B', 'C', 'B', 'D', 'A', 'B' };
	//char y[y_size + 1] = { '-', 'B', 'D', 'C', 'A', 'B', 'A' };			//'-' to reserve a bit
	int c[MAXSIZE][MAXSIZE], b[MAXSIZE][MAXSIZE];
	int x_size, y_size;
	//LCS_LENGTH(x, y, x_size, y_size, c, b);
	//printf_array(c, x_size, y_size);
	//PRINT_LCS(b, x, x_size, y_size);
	//printf("\n");

	char case1_x[] = "-xzyzzyx";
	char case1_y[] = "-zxyyzxz";
	x_size = strlen(case1_x);
	y_size = strlen(case1_y);
	LCS_LENGTH(case1_x, case1_y, x_size, y_size, c, b);
	PRINT_LCS(b, case1_x, x_size, y_size);
	printf("\n");

	char case2_x[] = "-MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCALLAAQANKESSSESFISRLLAIVAD";
	char case2_y[] = "-MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCTLLAAQANKENSNESFISRLLAIVAG";
	x_size = strlen(case2_x);
	y_size = strlen(case2_y);
	LCS_LENGTH(case2_x, case2_y, x_size, y_size, c, b);
	PRINT_LCS(b, case2_x, x_size, y_size);
	printf("\n");

	system("pause");
	return 0;
}

void printf_array(int c[][MAXSIZE], int i, int j)
{
	for (int a = 0; a <= i; a++)
	{
		for (int b = 0; b <= j; b++)
		{
			printf("%-3d", c[a][b]);
		}
		printf("\n");
	}
		
}

void LCS_LENGTH(char x[], char y[], int x_array_size, int y_array_size, int c[][MAXSIZE], int b[][MAXSIZE])
{
	for (int i = 1; i <= x_array_size; i++)
		c[i][0] = 0;
	for (int j = 0; j <= y_array_size; j++)
		c[0][j] = 0;
	for (int i = 1; i <= x_array_size; i++)
	{
		for (int j = 1; j <= y_array_size; j++)
		{
			if (x[i] == y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = TOP_LEFT;
			}
			else
			{
				c[i][j] = (c[i - 1][j] >= c[i][j - 1]) ? c[i - 1][j] : c[i][j - 1];
				b[i][j] = (c[i - 1][j] >= c[i][j - 1]) ? TOP : LEFT;
			}
		}
	}
}

void PRINT_LCS(int b[][MAXSIZE], char x[], int i, int j)
{
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == TOP_LEFT)
	{
		PRINT_LCS(b, x, i - 1, j - 1);
		printf("%-3c", x[i]);
	}
	else if (b[i][j] == TOP)
	{
		PRINT_LCS(b, x, i - 1, j);
	}
	else
	{
		PRINT_LCS(b, x, i, j - 1);
	}	
}