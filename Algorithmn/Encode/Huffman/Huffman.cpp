#include <iostream>
#include <stdlib.h>
#include <string>
#define num 8
#define MAXSIZE 100
using namespace std;

class coded_char
{
private:
	char value;
	double weight;
	string code;
	bool iscoded = false;

public:
	coded_char(char value, double weight) :value(value), weight(weight){}

	coded_char* left, *right;

	void setcode(string s){code = s;}
	string getcode(){return code;}
	double getweight(){return weight;}
	bool getiscoded(){return iscoded;}
	void setiscoded(){iscoded = true;}
	char getvalue(){return value;}
};

coded_char* get_last(coded_char* data[], int end)
{
	double min = 9999.0;
	coded_char* last = data[0];
	for (int i = 0; i < end; i++)
	{
		if ((*data[i]).getiscoded() == true)
			continue;
		if ((*data[i]).getweight() < min)
		{
			min = (*data[i]).getweight();
			last = data[i];
		}
	}

	return last;
}

coded_char* get_second_last(coded_char* data[], coded_char* last, int end)
{
	double min = 9999.0;
	coded_char* second_last = data[0];
	for (int i = 0; i < end; i++)
	{
		if ((*data[i]).getiscoded() == true)
			continue;
		if ((*data[i]).getweight() < min && data[i] != last)
		{
			min = (*data[i]).getweight();
			second_last = data[i];
		}
	}

	return second_last;
}

void trace(coded_char* root)
{
	if ((*root).getvalue() != ' ')
	{
		return;
	}
	else
	{
		(*((*root).left)).setcode((*root).getcode() + "0");
		(*((*root).right)).setcode((*root).getcode() + "1");
		trace((*root).left);
		trace((*root).right);
	}
}

void HUFFMAN_CODE(coded_char* data[])
{
	for (int i = num; i < 2 * num - 1; i++)
	{
		coded_char* last = get_last(data, i);
		coded_char* second_last = get_second_last(data, last, i);
		data[i] = new coded_char(' ', (*last).getweight() + (*second_last).getweight());
		(*data[i]).left = last;
		(*data[i]).right = second_last;
		(*last).setiscoded();
		(*second_last).setiscoded();
	}

	(*data[2 * num - 2]).setcode("");	//root
	trace(data[2 * num - 2]);
}

void print_code(coded_char* data)
{
	cout << (*data).getvalue() << ":" << (*data).getcode() << endl;
}

int main()
{
	coded_char* data[2 * num - 1];

	data[0] = new coded_char('A', 1);
	data[1] = new coded_char('B', 1);
	data[2] = new coded_char('C', 1);
	data[3] = new coded_char('D', 2);
	data[4] = new coded_char('E', 3);
	data[5] = new coded_char('F', 5);
	data[6] = new coded_char('G', 5);
	data[7] = new coded_char('H', 10);
	
	HUFFMAN_CODE(data);
	for (int k = 0; k < num; k++)
		print_code(data[k]);
	//cout << (*last).getvalue() << ' ' << (*second_last).getvalue() << endl;


	system("pause");
	return 0;
}