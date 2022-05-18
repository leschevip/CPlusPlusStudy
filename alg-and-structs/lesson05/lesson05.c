#include <stdio.h>

void print1dArray(int* arr, int size)
{
	for (int j=0; j < size; ++j)
		printf("%4d", arr[j]);
	printf("\n");
}

int* init1dArray(int size)
{
	return (int*)calloc(sizeof(int), size);
}

void fill1dArray(int* arr, int size, int bound)
{
	srand(time(NULL));
	for (int i=0; i < size; ++i)
		arr[i] = rand() % bound;
}

int** init2dArray(int** arr, int row, int col)
{
	arr = (int**) calloc(sizeof(int*), row);
	for (int i=0; i < row; ++i)
		*(arr + i) = (int*) calloc(sizeof(int), col);
	return arr;
}

void free2dArray(int** arr, int size)
{
	for (int i=0; i < size; ++i)
		free(arr[i]);
	free(arr);
}

void sortInserts(int* arr, int start, int end, int (*cond) (int a, int b))
{
	for (int i = start + 1; i <= end; i++)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if ((cond == 0 && arr[j] > arr[j+1]) || (cond != 0 && cond(arr[j], arr[j+1])))
			{
				int tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
			else
			{
				break;
			}
		}
	}
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/* ------------- task 1 -------------*/
static int* qsArray;

int condition(int a, int b)
{
	return qsArray[a] > qsArray[b];
}

void qsBetter(int start, int end, int border)
{
	if (end - start + 1 > border)
	{
		int mid = (start + end)/2;
		int idx[3] = {start, end, mid};
		sortInserts(idx, 0, 2, condition);
		if (mid != idx[1])
		{
			swap(&qsArray[mid], &qsArray[idx[1]]);
		}


		int x = qsArray[mid];
		int i = start;
		int j = end;

		do
		{
			while (qsArray[i] < x) i++;
			while (qsArray[j] > x) j--;

			if (i <= j)
			{
				swap(&qsArray[i], &qsArray[j]);
				i++;
				j--;
			}
		}
		while (i <= j);

		if (i < end)
			qsBetter(i, end, border);
		if (j > start)
			qsBetter(start, j, border);
	}
	else
	{
		sortInserts(qsArray, start, end, 0);
	}
}

/* ------------- task 2 -------------*/

void printBuckets(int** buckets, int row, int col)
{
	int bIdx = 0;
	int nextStep = 0;

	printf("buckets: ");
	for(int i = 0; i < row; i++)
		printf("%6d", i);
	printf("\n");
	do
	{
		nextStep = 0;
		printf("         ");
		for(int i = 0; i < row; i++)
		{
			if (bIdx <= buckets[i][col - 1] - 1)
			{
				nextStep = 1;
				printf("%6d", buckets[i][bIdx]);
			}
			else
			{
				printf("      ");
			}
		}
		printf("\n");
		bIdx++;

	} while (nextStep);
}

int blockSort(int* arr, int size, unsigned int bucketCount, int isPrintBuckets)
{
	if (bucketCount == 0)
	{
		printf("Amount of buckets must be greater 0");
		return 0;
	}

	const int COUNTER_IDX = size;

	int** buckets;
	buckets = init2dArray(buckets, bucketCount, COUNTER_IDX + 1);
	for (int i = 0; i < bucketCount; i++)
		buckets[i][COUNTER_IDX] = 0;

	int digit = 1;
	int sortedCounts = 0;
	int count = 0;
	int countCalcucated = 0;

	do
	{
		for (int i = 0; i < COUNTER_IDX; i++)
		{
			if ((arr[i] & 1) == 0)
			{
				int d = (arr[i]/digit) % bucketCount;
				buckets[d][buckets[d][COUNTER_IDX]++] = arr[i];

				if (!countCalcucated)
					count++;
			}
		}

		if (!countCalcucated)
			countCalcucated = 1;
		sortedCounts = buckets[0][COUNTER_IDX];


		if (isPrintBuckets)
		{
			printf("digit %d\n", digit);
			printBuckets(buckets, bucketCount, COUNTER_IDX + 1);
		}


		int idx = 0;
		for (int i = 0; i  < bucketCount; i++)
		{
			for (int j = 0; j < buckets[i][COUNTER_IDX]; j++)
			{
				while ((arr[idx] & 1) != 0) idx++;
				arr[idx++] = buckets[i][j];
			}
			buckets[i][COUNTER_IDX] = 0;
		}

		digit *= bucketCount;

	} while (sortedCounts != count);

	free2dArray(buckets, bucketCount);

	return 1;
}

int main(int argv, char** argc)
{
	const int SIZE = 20;
	const int BORDER = 100;
	const int SORT_BORDER = 10;


	printf("Task1:\n");
	qsArray = init1dArray(SIZE);
	fill1dArray(qsArray, SIZE, BORDER);
	printf("Generated array:\n");
	print1dArray(qsArray, SIZE);
	qsBetter(0, SIZE - 1, SORT_BORDER);
	printf("Sorted array:\n");
	print1dArray(qsArray, SIZE);
	free(qsArray);


	printf("Task2:\n");
	const int PRINT_BUCKETS = 0;
	const int BUCKETS_COUNT = 5;
	qsArray = init1dArray(SIZE);
	fill1dArray(qsArray, SIZE, BORDER);
	printf("Generated array:\n");
	print1dArray(qsArray, SIZE);
	blockSort(qsArray, SIZE, BUCKETS_COUNT, PRINT_BUCKETS);
	printf("Sorted array:\n");
	print1dArray(qsArray, SIZE);
	free(qsArray);
	return 0;
}
