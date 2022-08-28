#include "ArrayInt.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void Task1()
{
	ArrayInt arr(3, 4);
	cout << arr << endl;
	arr.popFront();
	cout << arr << endl;
	arr.popFront();
	cout << arr << endl;
	arr.popFront();
	cout << arr << endl;

	ArrayInt arr2(4, 4);
	arr2[1] = 2;
	arr2[2] = 3;
	arr2[3] = 1;
	cout << arr2 << endl;
	arr2.sortAsc();
	cout << arr2 << endl;
}

void Task2()
{
	vector<int> arr{ 4, 4, 2, 3, 3, 1 };
	sort(begin(arr), end(arr));
	auto first = arr.begin();
	auto last = arr.end();
	int c = 0;
	while (first < last)
	{
		if (first == (last - 1) || *first != *(first + 1))
		{
			c++;
		}
		else
		{
			first++;
		}

		first++;
	}
	cout << "count " << c << endl;
}

void Task3()
{
	// Hand.h
	// Card.h
	// BlackJack.h
}

void main()
{
	Task1();
	Task2();
	Task3();
}