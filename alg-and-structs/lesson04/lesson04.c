#include <stdio.h>
#include <math.h>
#include <limits.h>

int* init1dArray(int size)
{
	return (int*)calloc(sizeof(int), size);
}

void input1dArr(int* arr, int size)
{
	printf("Write values:\n");
	for(int i = 0; i < size; ++i)
		scanf("%d", &arr[i]);
}

void print1dArray(int* arr, int size)
{
	for (int j=0; j < size; ++j)
		printf("%4d", arr[j]);
	printf("\n");
}


int** init2dArray(int** arr, int size)
{
	arr = (int**) calloc(sizeof(int*), size);
	for (int i=0; i < size; ++i)
		*(arr + i) = (int*) calloc(sizeof(int), size);
	return arr;
}

void fillRand2dArray(int** arr, int size, int bound)
{
	srand(time(NULL));
	for (int i=0; i < size; ++i)
		for (int j=0; j < size; ++j)
			arr[i][j] = rand() % bound;
}

void print2dArray(int** arr, int size)
{
	for (int i=0; i < size; ++i)
	{
		print1dArray(arr[i], size);
	}
}

void free2dArray(int** arr, int size)
{
	for (int i=0; i < size; ++i)
		free(arr[i]);
	free(arr);
}

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void bubbleSort2dArray(int** arr, int size)
{
	int len = size * size;
	for (int i = 0; i < len; i++)
	{
		int idx = 0;
		while (idx < len - 1)
		{
			int r1 = idx / size;
			int c1 = idx - (idx / size)*size;

			int r2 = (idx + 1) / size;
			int c2 = (idx + 1) - ((idx + 1)/ size)*size;

			if (arr[r1][c1] > arr[r2][c2])
				swap(&arr[r1][c1], &arr[r2][c2]);

			idx++;
		}
	}
}


double tpkFunc(double v)
{
	return sqrt(abs(v)) + 5*pow(v, (double)3);
}

void bubble()
{
	const int SIZE = 4;
	const int BORDER_VAL = 10;
	int** arr;
	arr = init2dArray(arr, SIZE);
	fillRand2dArray(arr, SIZE, BORDER_VAL);

	printf("Before:\n");
	print2dArray(arr, SIZE);
	bubbleSort2dArray(arr, SIZE);

	printf("After:\n");
	print2dArray(arr, SIZE);
	printf("\n");

	free2dArray(arr, SIZE);
}

void tpkAlgo()
{
	const int BORDER = 400;
	const int SIZE = 11;

	int* arr;
	arr = init1dArray(SIZE);
	input1dArr(arr, SIZE);
	print1dArray(arr, SIZE);

	for (int i = SIZE-1; i >= 0; i--)
	{
		if (tpkFunc(arr[i]) > BORDER)
			printf("Value %4d greater %d\n", arr[i], BORDER);
	}

	free(arr);
}

/*
@startuml
start
:установка констант BORDER и SIZE;
:выделение памяти для SIZE элементов массива ARR;
while (USER ввел менее чем SIZE элементов?) is (Да)
	:ожидание ввода данных;
	:запись введенного значения в массив ARR;
endwhile (Нет)
:вывод массива ARR на экран;
:определяем счетчик цикла i = SIZE - 1;
while (i >= 0) is (Да)
	:расчет ТПК функции в переменную TMP;
	if (TMP > BORDER) then (Да)
		:вывод уведомления USER;
	else (Нет)
	endif;
endwhile (Нет)

:освобождение памяти и выход;
end
@enduml
 */

int main(int argv, char** argc)
{
	bubble();

	tpkAlgo();

	return 0;
}
