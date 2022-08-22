
#include "figure.h"
#include "Car.h"
#include "Fraction.h"

void Task1()
{
	Figure* p = new Parallelogram(5, 2, 30);
	printFigure(p);
	Figure* c = new Circle(1);
	printFigure(c);
	Figure* rect = new Rectangle(1, 2);
	printFigure(rect);
	Figure* sq = new Square(2);
	printFigure(sq);
	Figure* romb = new Rhombus(1, 2);
	printFigure(romb);

	delete p;
	delete c;
	delete rect;
	delete sq;
	delete romb;
}

void Task2()
{
	cout << "Car:" << endl;
	Car c("Porshe", "911");
	cout << endl;
	cout << "PassengerCar:" << endl;
	PassengerCar pc("Porshe", "911");
	cout << endl;
	cout << "Bus:" << endl;
	Bus b("ËÀÇ", "695");
	cout << endl;
	cout << "Minivan:" << endl;
	Minivan m("Porshe", "911");
	cout << endl;
	system("pause");
}

void Task3()
{
	Fraction f1(1, 2);
	Fraction f2(3, 4);
	Fraction f3 = f1 + f2;
	cout << f3 << endl;
	Fraction f4 = -f3;
	cout << f4 << endl;
	Fraction f5 = f4 - f1;
	cout << f5 << endl;
	Fraction f6 = f5 * f2;
	cout << f6 << endl;
	Fraction f7 = f6 / f5;
	cout << f7 << endl;

	cout << (f7 < f6) << endl;
}

void main()
{
	Task1();
	Task2();
	Task3();
}