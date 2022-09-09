#include "func.h"
#include <string>
#include <iostream>
#include "Ex.h"
#include <conio.h>
#include "robot.h"


using namespace std;

void Task1()
{
	try
	{
		auto v = divv(2, 0.0f);
		cout << v << endl;
	}
	catch (const char* ex)
	{
		cerr << ex << endl;
	}
}

void Task2()
{
	double a;
	Bar b;
	do
	{
		try
		{
			cout << "Input v: ";
			cin >> a;
			cout << endl;
			
			b.Set(a);
		}
		catch (Ex& ex)
		{
			cerr << "error code: " << ex.what() << endl;
		}
		catch (...)
		{
			cerr << "Application error" << endl;
		}
	} while (a != 0);
}

void Task3()
{
	Robot r(10, 10, 2, 3);
	cout << r << endl << endl;

	while (true)
	{
		if (_kbhit())
		{
			int c = 0;
			while (_kbhit())
			{
				c = _getch();
			}
			
			try
			{
				r.move(c);
				system("cls");
				cout << r << endl;
			}
			catch (IllegalCommand& ex)
			{
				cerr << ex.what() << endl;
			}
			catch (OffTheField& ex)
			{
				cerr << ex.what() << endl;
			}
		}
				
	}
}


void main()
{
	Task1();
	Task2();
	Task3();
}