#include <stdio.h>

void printArray(char *arr, int size)
{
	for (int i=0; i < size; i++)
		printf("%c", arr[i]);
}

char open[3] = {'(', '[', '{'};
char close[3] = {')', ']', '}'};

int checkExprRecurse(char *arr, int idx, int bracketIdx, int size)
{
	int t = 0;

	while (idx < size)
	{
		for (int i = 0; i < 3; i++)
		{
			if (bracketIdx == -1 && arr[idx] == close[i])
			{
				return -1;
			}
			else if (bracketIdx != -1 && close[i] != close[bracketIdx] && arr[idx] == close[i])
			{
				return -1;
			}
			else if (bracketIdx != -1 && close[i] == close[bracketIdx] && arr[idx] == close[i])
			{
				return idx;
			}
		}

		int skip = 1;
		for (t = 0; t < 3; t++)
		{
			if (arr[idx] == open[t])
			{
				skip = 0;
				break;
			}
		}

		if (skip == 1)
			idx++;
		else
		{
			idx = checkExprRecurse(arr, idx + 1, t, size);
			if (idx < 0)
				return -1;
			idx++;
		}
	}

	return bracketIdx != -1 ? -1 : idx;
}

void checkExpr(char *arr, int size)
{
	printArray(arr, size);
	int idx = checkExprRecurse(arr, 0, -1, size);
	printf( idx < 0 ? " <-- error\n" : " <-- all good\n");
}

void Task1()
{
	char strGood1[2] = {'(', ')'};
	char strGood2[6] = {'(', '[', ']', ')', '(', ')'};
	char strGood3[4] = {'{', '}', '(', ')' };
	char strGood4[6] = {'(', '[', '{', '}', ']', ')'};

	char strBad1[2] = {')', '('};
	char strBad2[6] = {'(', ')', ')', '(', '{', ')'};
	char strBad3[1] = {'('};
	char strBad4[4] = {']', ')', '}', ')'};
	char strBad5[5] = {'(', '[', '(', ']', ')'};

	char ex1[9] = {'(', '2', '+', '(', '2', '*', '2', ')', ')'};
	char ex2[13] = {'[', '2', '/', '{', '5', '*', '(', '4', '+', '7', ')', '}', ']'};

	char s1[11] = { '(', '(', '[', '[', ']', '}', ')', ']', ')', '{', '}' };
	char s2[10] = { '(', '(', '[', '[', ']', ']', ')', ')', '{', '}' };


	checkExpr(strGood1, 2);
	checkExpr(strGood2, 6);
	checkExpr(strGood3, 4);
	checkExpr(strGood4, 6);
	checkExpr(strBad1, 2);
	checkExpr(strBad2, 6);

	checkExpr(strBad3, 1);

	checkExpr(strBad4, 4);
	checkExpr(strBad5, 5);
	checkExpr(ex1, 9);
	checkExpr(ex2, 13);

	checkExpr(s1, 11);
	checkExpr(s2, 10);
}


typedef struct Node
{
	int data;
	struct Node *next;
} Node;

typedef struct List
{
	int size;
	Node *head;
} List;

void initList(List * list)
{
	list->head = NULL;
	list->size = 0;
}

void insNode(List *list, int data)
{
	Node *new = (Node*)malloc(sizeof(Node));
	new->data = data;
	new->next = NULL;

	Node* curr = list->head;
	if (curr == NULL)
	{
		list->head = new;
		list->size++;
	}
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new;
		list->size++;
	}
}

Node* remNode(List *list, int data)
{
	Node *cur = list->head;
	Node *par = NULL;

	if (cur == NULL)
		return NULL;

	while (cur->next != NULL && cur->data != data)
	{
		par = cur;
		cur = cur->next;
	}

	if (cur->data != data)
		return NULL;
	if (cur == list->head)
	{
		list->head = cur->next;
		list->size--;
		return cur;
	}
	par->next = cur->next;
	list->size--;
	return cur;
}

List* cloneList(List* list)
{
	if (list == NULL)
		return NULL;

	List * cloneList = (List*)malloc(sizeof(List));
	initList(cloneList);
	if (list->size == 0)
	{
		return cloneList;
	}

	Node* cur = list->head;
	while(cur != NULL)
	{
		insNode(cloneList, cur->data);
		cur = cur->next;
	}
	return cloneList;
}

int isSortedAscList(List *list)
{
	if (list == NULL)
		return 0;

	Node *cur = list->head;
	if (cur != NULL)
	{
		int min = cur->data;
		while(cur->next != NULL)
		{
			cur = cur->next;
			if (min > cur->data)
				return 0;
			else
				min = cur->data;
		}
	}

	return 1;
}

void printListNode(Node * node)
{
	if (node == NULL)
	{
		printf("[]");
		return;
	}
	printf("[%d] ", node->data);
}

void printList(List *list)
{
	Node *cur = list->head;
	if (cur == NULL)
	{
		printListNode(cur);
	}
	else
	{
		do
		{
			printListNode(cur);
			cur = cur->next;
		}
		while (cur != NULL);
	}
	printf("\n");
}

void freeList(List * list)
{
	Node* cur = list->head;
	while (cur != NULL)
	{
		Node * next = cur->next;
		free(cur);
		cur = next;
	}
	free(list);
}


void Task2()
{
	List *list = (List*)malloc(sizeof(List));
	initList(list);
	insNode(list, 1);
	insNode(list, 2);
	insNode(list, 3);
	insNode(list, 4);
	printList(list);


	List *newList = cloneList(list);
	printList(newList);

	freeList(list);
	freeList(newList);
}



void Task3()
{
	List *list = (List*)malloc(sizeof(List));
	initList(list);
	insNode(list, 1);
	insNode(list, 2);
	insNode(list, 3);
	insNode(list, 1);
	printList(list);

	printf(isSortedAscList(list) == 1 ? "sorted\n" : "not sorted\n");
	freeList(list);
}

int main(int argv, char** argc)
{
	Task1();
	Task2();
	Task3();
}
