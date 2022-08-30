
#include <iostream>
#include "Pair1.h"
#include "Pair.h"
#include "StringValuePair.h"
#include "GenericPlayer.h"

using namespace std;

void Task1()
{
	Pair1<int> p1(6, 9);
	cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair1<double> p2(3.4, 7.8);
	cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
}

void Task2()
{
	Pair<int, double> p1(6, 7.8);
	cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair<double, int> p2(3.4, 5);
	cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
}

void Task3()
{
	StringValuePair<int> svp("Amazing", 7);
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
}

void main()
{
	Task1();
	Task2();
	Task3();

	InputNumber<bool>(NAME_OF(a));
}