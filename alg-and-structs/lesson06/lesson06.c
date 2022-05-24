#include <stdio.h>

#define SZ 9

typedef struct {
	int index;
	int data;
} node;

node* array[SZ];

int head;
int tail;
int items;

void init()
{
	for (int i = 0; i < SZ; ++i)
	{
		array[i] = NULL;
	}
	head = 0;
	tail = -1;
	items = 0;
}

void insert2(int index, int data)
{
	node* nd = (node*)malloc(sizeof(node));
	nd->index = index;
	nd->data = data;

	if (items < SZ)
	{
		array[++tail] = nd;
		items++;
	}
	else
	{
		printf("%s \n", "Queue is full");
	}
}

node* rem2()
{
	if (tail >= head)
	{
		int curPr = array[head]->index;
		int priorIdx = 0;
		for (int i = tail; i > head; --i)
		{
			if (array[i]->index < curPr)
			{
				curPr = array[i]->index;
				priorIdx = i;
			}
		}

		node* tmp = array[priorIdx];
		for (int i = priorIdx; i < tail; i++)
		{
			array[i] = array[i + 1];
		}
		array[tail] = NULL;
		tail--;
		items--;

		return tmp;
	}
	else
	{
		printf("%s \n", "Queue is empty");
		return NULL;
	}
}

void printQueue()
{
	printf("[ ");
	for (int i = 0; i < SZ; ++i)
	{
		if (array[i] == NULL)
			printf("[*,*] ");
		else
			printf("[%d, %d] ", array[i]->index, array[i]->data);
	}
	printf(" ] \n");
}

void Task1()
{
	init();

	insert2(6,100);
	insert2(3,200);
	insert2(2,300);
	insert2(4,400);
	insert2(4,500);
	insert2(3,600);
	insert2(6,700);
	insert2(7,800);
	insert2(4,900);

	printQueue();

	rem2();

	printQueue();

	insert2(1,950);

	printQueue();
}

typedef int bool;
#define BIT 32
#define T char
#define true 1 == 1
#define false 1 != 1


T stack[BIT];
int vertex;

void initStack()
{
	for (int i = 0; i < BIT; i++)
		stack[i] = NULL;
	vertex = -1;
}


bool push(int val)
{
	if (vertex < BIT)
	{
		stack[++vertex] = val;
		return true;
	}
	else
	{
		printf("%s \n", "Stack Overflow");
		return false;
	}
}

T pop()
{
	if (vertex != -1)
	{
		return stack[vertex--];
	}
	else
	{
		printf("%s \n", "Stack is empty");
		return -1;
	}
}

T seek()
{
	if (vertex != -1)
		return stack[vertex];
	else
	{
		printf("%s \n", "Stack is empty");
		return -1;
	}
}

void translate(int v)
{
	initStack();
	int tmp = v;
	const int base = 2;
	while (tmp != 0)
	{
		push(tmp % base);
		tmp /= base;
	}
}

void Task2()
{
	const int value = 2057;
	translate(value);
	printf("value %d translated: ", value);
	while (vertex != -1)
		printf("%d", pop());
	printf("\n");
}


int main(int argv, char** argc)
{
	Task1();
	Task2();
}
