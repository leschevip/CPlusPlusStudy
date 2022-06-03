#include <stdio.h>

#define T char
#define true 1 == 1
#define false 1 != 1
#define GRAPH_SZ 6
#define GRAPH_ROBOT_SZ 14

#define MIN_MAX 2147483647;

typedef int boolean;

typedef struct IntStackArray
{
	int* head;
	int size;
	int index;
} IntStackArray;

int matrix[GRAPH_SZ][GRAPH_SZ] =
{
	{0, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0}
};

int graph_robot[GRAPH_ROBOT_SZ][GRAPH_ROBOT_SZ] =
{
  // A B C D E F G H I J K L M N
	{0,1,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,1,0,0,0,1,0,0,0,1,0,0,0},
	{0,0,1,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,0}
};


void initIntArray(int* a, int sz)
{
	for(int i = 0; i < sz; i++)
		a[i] = 0;
}

IntStackArray* initStackArray(int sz)
{
	IntStackArray *stack = (IntStackArray*)malloc(sizeof(IntStackArray));
	stack->head = (int*)malloc(sizeof(int)*sz);
	stack->size = sz;
	stack->index = -1;
	initIntArray(stack->head, sz);
	return stack;
}

void freeStackArray(IntStackArray* stack)
{
	free(stack->head);
	free(stack);
}

boolean push(IntStackArray* stack, int data)
{
	if (stack->index < stack->size)
	{
		stack->head[++stack->index] = data;
		return true;
	}
	else
	{
		printf("%s \n", "Stack overflow");
		return false;
	}
}

int pop(IntStackArray* stack)
{
	if (stack->index != -1)
	{
		return stack->head[stack->index--];
	}
	else
	{
		return MIN_MAX;
	}
}

int seek(IntStackArray *stack)
{
	if (stack->index != -1)
	{
		return stack->head[stack->index];
	}
	else
	{
		return MIN_MAX;
	}
}

void depthGraph(int sz, int item)
{
	if (item > sz)
	{
		printf("No such graph item");
		return;
	}

	int visited[sz];
	initIntArray(visited, sz);

	IntStackArray* stack = initStackArray(sz);
	push(stack, item);
	visited[item - 1] = 1;
	printf("[%d]", item);

	while (stack->index != -1)
	{
		int cur = seek(stack);
		boolean next = false;
		for (int k = 0; k < sz; k++)
		{
			if (matrix[cur - 1][k] == 1 && !visited[k])
			{
				next = push(stack, k + 1);
				visited[k] = 1;
				printf("[%d]", k + 1);
				break;
			}
		}

		if (!next)
			pop(stack);
	}

	freeStackArray(stack);
}

void printIntArray(int* array, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d", array[i]);
        if (i != size - 1)
            printf(",");
    }
    printf("\n");
}

int get2dInt(int** array, const int row, const int col) {
    return *((*(array + row)) + col);
}

void print2dIntArray(int** array, const int row, const int col, int offset) {
    char format[7];
    sprintf(format, "%%%dd", offset);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf(format, get2dInt(array, i, j));
        }
        printf("\n");
    }
}

void swap(int* arr, int a, int b, int* more)
{
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;

	if (more != 0)
		swap(more, a, b, 0);
}

void sortInserts(int* arr, int start, int end, int* more)
{
	for (int i = start + 1; i <= end; i++)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (arr[j] < arr[j+1])
			{
				swap(arr, j, j + 1, more);
			}
			else
			{
				break;
			}
		}
	}
}

void qsBetter(int *qsArray, int start, int end, int border, int *desc)
{
	if (end - start + 1 > border)
	{
		int mid = (start + end)/2;
		int idx[3] = {start, end, mid};
		sortInserts(idx, 0, 2, 0);
		if (mid != idx[1])
		{
			swap(qsArray, mid, idx[1], desc);
		}


		int x = qsArray[mid];
		int i = start;
		int j = end;

		do
		{
			while (qsArray[i] > x) i++;
			while (qsArray[j] < x) j--;

			if (i <= j)
			{
				swap(qsArray, i, j, desc);
				i++;
				j--;
			}
		}
		while (i <= j);

		if (i < end)
			qsBetter(qsArray, i, end, border, desc);
		if (j > start)
			qsBetter(qsArray, start, j, border, desc);
	}
	else
	{
		sortInserts(qsArray, start, end, desc);
	}
}

int* inDegreeByMatrix()
{
	int *arr = (int*)malloc(sizeof(int)*GRAPH_ROBOT_SZ);;
	initIntArray(arr, GRAPH_ROBOT_SZ);

	for (int i = 0; i < GRAPH_ROBOT_SZ; i++)
		for (int j = 0; j < GRAPH_ROBOT_SZ; j++)
			arr[i]+= graph_robot[j][i];

	return arr;
}

void printTaskMatrix()
{
	printf("    ");
	for (int i = 0; i < GRAPH_ROBOT_SZ; i++)
	{
		printf("%c", i+65);
		if (i != GRAPH_ROBOT_SZ - 1)
			printf(" ");
	}
	printf("\n");
	for (int i = 0; i < GRAPH_ROBOT_SZ; ++i) {
		printf("%c [ ", i+65);
			for (int j = 0; j < GRAPH_ROBOT_SZ; ++j) {
				printf("%d ", graph_robot[i][j]);
			}
			printf("]\n");
		}
}

void printTaskResult(int* res)
{
	for (int i = 0; i < GRAPH_ROBOT_SZ; i++)
	{
		printf("%c", res[i]+65);
		if (i != GRAPH_ROBOT_SZ - 1)
			printf(",");
	}
}

void Task1()
{
	depthGraph(GRAPH_SZ, 1);
	printf("\n");
	depthGraph(GRAPH_SZ, 3);
	printf("\n");
	depthGraph(GRAPH_SZ, 2);
	printf("\n");
}

void Task2()
{
	printTaskMatrix();

	int* degrees = inDegreeByMatrix();
	printf("Полустепень захода:\n    ");
	printIntArray(degrees, GRAPH_ROBOT_SZ);
	printf("\n");
	int *res = (int*)malloc(sizeof(int)*GRAPH_ROBOT_SZ);
	for (int i = 0; i < GRAPH_ROBOT_SZ; i++)
		res[i] = i;

	qsBetter(degrees, 0, GRAPH_ROBOT_SZ - 1, GRAPH_ROBOT_SZ / 2, res);

	printf("Отсортированные в обратном порядке узлы в порядке уменщения количества ссылок на них:\n    ");
	printTaskResult(res);

	printf("\n");

	free(degrees);
	free(res);
}

void inDegreeRecursive(int item, int* res, int* visited)
{
	 visited[item] = 1;

	 for (int i = 0; i < GRAPH_ROBOT_SZ; i++)
	 {
		 if (graph_robot[item][i] == 1)
		 {
			 res[i]++;
			 if (!visited[i])
				 inDegreeRecursive(i, res, visited);
		 }
	 }
}


void Task3(int n)
{
	printTaskMatrix();

	int *visited = (int*)malloc(sizeof(int)*GRAPH_ROBOT_SZ);
	initIntArray(visited, GRAPH_ROBOT_SZ);
	int *degrees = (int*)malloc(sizeof(int)*GRAPH_ROBOT_SZ);
	initIntArray(degrees, GRAPH_ROBOT_SZ);

	inDegreeRecursive(n, degrees, visited);

	printf("Полустепень захода:\n    ");
	printIntArray(degrees, GRAPH_ROBOT_SZ);
	printf("\n");
	int *res = (int*)malloc(sizeof(int)*GRAPH_ROBOT_SZ);
	for (int i = 0; i < GRAPH_ROBOT_SZ; i++)
		res[i] = i;

	qsBetter(degrees, 0, GRAPH_ROBOT_SZ - 1, GRAPH_ROBOT_SZ / 2, res);

	printf("Отсортированные в обратном порядке узлы в порядке уменщения количества ссылок на них:\n    ");
	printTaskResult(res);
	printf("\n");

	free(degrees);
	free(res);
	free(visited);
}


int main(int argv, char** argc)
{
	Task1();
	printf("\n");
	Task2();
	printf("\n");
	Task3(0);
	return 0;
}
