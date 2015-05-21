#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
using namespace std;
double weight[4];

long double ARITHMETIC_CODING(char* input)
{
	long double start = 0;
	long double end = 1;
	char extract[3];
	if (strlen(input) % 2 != 0)
		return -1.0;
	else
	{
		char* ch = input;
		while (*ch != '\0')
		{
			extract[0] = *ch++;
			extract[1] = *ch++;
			extract[2] = '\0';
			char* extract_string = extract;
			if (!strcmp(extract_string, "11"))
			{
				start = end - (end - start) * weight[3];
			}
			else if (!strcmp(extract_string, "10"))
			{
				long double e = end - (end - start) * weight[3];
				long double s = end - (end - start) * (weight[3] + weight[2]);
				end = e;
				start = s;
			}
			else if (!strcmp(extract_string, "01"))
			{
				long double e = end - (end - start) * (weight[3] + weight[2]);
				long double s = start + (end - start) * (weight[0]);
				end = e;
				start = s;
			}
			else
			{	//"00"
				end = start + (end - start) * (weight[0]);
			}
			cout.precision(20);										//…Ë÷√æ´∂»£¨∑¿÷πÀ ß
			printf("start: %.12lf, end: %.12lf\n", start, end);
		}
		return (start + end) / 2;
	}
}

int main()
{
	/* input weight */
	
	weight[3] = 0.3;	//"11"
	weight[2] = 0.2;	//"10"
	weight[1] = 0.4;	//"01"
	weight[0] = 0.1;	//"00"
	//cout << "Weight:" << endl;
	//do
	//{
	//	cout << "11:";
	//	cin >> weight[3];
	//} while (weight[3] < 0.0 || weight[3] > 1.0);
	//do
	//{
	//	cout << "10:";
	//	cin >> weight[2];
	//} while (weight[2] < 0.0 || weight[2] > 1.1 - (weight[3] + 0.1));
	//do
	//{
	//	cout << "01:";
	//	cin >> weight[1];
	//} while (weight[1] < 0.0 || weight[1] > 1.1 - (weight[3] + weight[2] + 0.1));
	//
	//do
	//{
	//	cout << "00:";
	//	cin >> weight[0];
	//} while (weight[0] < 0.0 || weight[0] > 1.1- (weight[3] + weight[2] + weight[1] + 0.1));

	printf("%.12lf\n", ARITHMETIC_CODING("10001100101101"));
	//cout << ARITHMETIC_CODING("10001100101101") << endl;


	system("pause");
	return 0;
}