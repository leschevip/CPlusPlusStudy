//#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include "Matrix.h"

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
	Matrix<int, 4> m;
	m.FillRandom(-100, 100);
	cout << m << endl;
}

int main()
{
	Task1();
	Task2();
	return 0;
}
