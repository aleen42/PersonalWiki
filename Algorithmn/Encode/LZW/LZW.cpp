#include <iostream>
#define MAXSIZE 100
using namespace std;


class dictionary
{
private:
	int index;
	char value[MAXSIZE];
	int code;
public:
	dictionary(int index, char value[]) :index(index){ strcpy((*this).value, value); };
	char* get_value(){ return value; }
	int get_index(){ return index; }
	void set_code(int set){ code = set; }
	int get_code(){ return code; }
};

dictionary* d[MAXSIZE];
int num;		//表示当前词典内元素的个数
int _count;		//初始化词典内元素的个数

char decode_output[MAXSIZE] = "";

char extract_last(char* input)
{
	char* ch = input;
	while (*ch++ != '\0');
	return *(ch - 2);
}

void LZW_DECODING()
{
	cout << "DeCode: ";
	for (int i = _count; i < num; i++)
	{
		int code = (*d[i]).get_code();
		cout << (*d[code - 1]).get_value();
	}
	cout << endl;
}

void LZW_CODING(const char* input)
{
	const char* ch = input;
	int count = 1;					//用于char指针跳转
	while (*(ch + 1) != '\0')
	{
		char a[MAXSIZE];
		bool isexisted = false;
		for (int i = 0; i < num; i++)
		{
			strncpy(a, ch, count + 1);
			a[count + 1] = '\0';

			if (!strcmp((*d[i]).get_value(),a))
			{
				isexisted = true;
				break;
			}
		}
		if (isexisted == false)
		{
			char b[MAXSIZE];
			strncpy(b, ch, count);
			b[count] = '\0';
			for (int i = 0; i < num; i++)
			{
				if (!strcmp((*d[i]).get_value(), b))
				{
					d[num++] = new dictionary(num + 1, a);
					(*d[num - 1]).set_code((*d[i]).get_index());
					break;
				}
			}
			ch += count;
			count = 1;
		}
		else
		{
			count++;
		}
	}

	for (int i = 0; i < num; i++)
	{
		if ((*((*d[i]).get_value()) == extract_last((*d[num - 1]).get_value())))
		{
			d[num++] = new dictionary(num + 1, "");
			(*d[num - 1]).set_code((*d[i]).get_index());
			break;
		}
	}

	cout << "EnCode: ";
	for (int i = _count; i < num; i++)
		cout << (*d[i]).get_code();
	cout << endl;
}

void INITIALIZE_DICTIONARY(const char* input)
{
	const char* ch = input;
	
	while (*ch != '\0')
	{
		bool isexisted = false;
		for (int i = 0; i < num; i++)
		{
			if (*(*d[i]).get_value() == *ch)
				isexisted = true;
		}
		if (isexisted == false)
		{
			char a[MAXSIZE];
			strncpy(a, ch, 1);
			a[1] = '\0';
			d[num++] = new dictionary(num + 1, a);
		}
		ch++;
	}
}


int main()
{
	/* Case 1 */
	num = 0;
	INITIALIZE_DICTIONARY("ABABCDEFGEFG");
	_count = num;
	//for (int i = 0; i < num; i++)
	//	cout << (*d[i]).get_index() << ' ' << (*d[i]).get_value() << endl;
	//LZW_CODING("ABBABABAC");
	LZW_CODING("ABABCDEFGEFG");

	LZW_DECODING();

	/* Case 2 */
	num = 0;
	INITIALIZE_DICTIONARY("ABBABABAC");
	_count = num;
	LZW_CODING("ABBABABAC");

	LZW_DECODING();

	system("pause");
	return 0;
}