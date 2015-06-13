#include <iostream>
#include <stdlib.h>
#define MAXSIZE 100

typedef struct{
	int weight;
	int value;
	double get;
}goods;

class Node
{
private: 
	int weight;
	int value;
public:
	Node* children[MAXSIZE];
	Node* parent = NULL;
	Node(int weight, int value) :weight(weight), value(value){}
	int get_weight(){ return (*this).weight; }
	int get_value(){ return (*this).value; }
};

int max_value = 0;
Node* max_node = NULL;

void BACK_TRACE(Node* root, int children_num, goods g[], int choose[])
{
	for (int i = 0; i < children_num; i++)
	{
		if ((*root).get_weight() - g[i].weight >= 0 && !choose[i])
		{
			int d[MAXSIZE];
			for (int j = 0; j < children_num; j++)
				d[j] = choose[j];
			d[i] = 1;
			(*root).children[i] = new Node((*root).get_weight() - g[i].weight, (*root).get_value() + g[i].value);
			(*((*root).children[i])).parent = root;

			if ((*root).get_value() + g[i].value > max_value)
			{
				max_value = (*root).get_value() + g[i].value;
				max_node = (*root).children[i];
			}
			BACK_TRACE((*root).children[i], children_num, g, d);
		}
		else
			(*root).children[i] = NULL;
	}
}

void TRACE_MAX(Node* max_node, int children_num,goods g[])
{
	for (int i = 0; i < children_num; i++)
	{
		if ((*((*max_node).parent)).children[i] == max_node)
		{
			g[i].get = 1;
			break;
		}
	}
	if ((*((*max_node).parent)).parent == NULL)
	{
		return;
	}
	TRACE_MAX((*max_node).parent, children_num, g);
}

int main()
{
	goods g[MAXSIZE];

	int size = 5;
	int capacity = 100;
	g[0].value = 20;
	g[0].weight = 10;

	g[1].value = 30;
	g[1].weight = 20;

	g[2].value = 65;
	g[2].weight = 30;

	g[3].value = 60;
	g[3].weight = 50;

	g[4].value = 40;
	g[4].weight = 40;

	for (int i = 0; i < size; i++)
		g[i].get = 0;

	int is_chosen[MAXSIZE];
	for (int i = 0; i < size; i++)
		is_chosen[i] = 0;
	Node* root = new Node(capacity, 0);
	BACK_TRACE(root, size, g, is_chosen);
	TRACE_MAX(max_node, size, g);
	printf("value   weight  get\n");
	for (int i = 0; i < size; i++)
	{
		printf("%-7d %-7d %-7lf\n", g[i].value, g[i].weight, g[i].get);
	}

	printf("%d\n", max_value);


	system("pause");
	return 0;
}