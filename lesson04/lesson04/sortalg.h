
void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void sortInserts(int* arr, int start, int end, int (*cond) (int& a, int& b))
{
	for (int i = start + 1; i <= end; i++)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if ((cond == 0 && arr[j] > arr[j + 1]) || (cond != 0 && cond(arr[j], arr[j + 1])))
			{
				swap(&arr[j], &arr[j + 1]);
			}
			else
			{
				break;
			}
		}
	}
}

int greaterCond(int& a, int& b)
{
	return a > b;
}

void sortIntAscInserts(int* arr, int start, int end)
{
	sortInserts(arr, start, end, greaterCond);
}