//#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include "Mtx.h"
#include "MyIterator.h"
#include "MyContainer.h"

using namespace std;


void Task1()
{
	cout << "Task1:" << endl;
	vector<double> v{ 0.5, 1.8 };
	v.push_back(accumulate(v.begin(), v.end(), 0.0) / v.size());
	for_each(v.begin(), v.end(), [](double val) { cout << val << " "; });
	cout << endl;
}

void Task2()
{
	cout << "Task2:" << endl;
	Mtx<int, 4> m;
	m.FillRandom(-100, 100);
	cout << m << endl;

	cout << m.Det() << endl;
}

void Task3()
{
	cout << "Task3:" << endl;
	MyContainer<int> values(3);
	values[0] = 1;
	values[1] = 2;
	values[2] = 3;
	for (auto v : values)
	{
		cout << v << "  ";
	}
	cout << endl;
}

int main()
{
	Task1();
	Task2();
	Task3();
	return 0;
}
