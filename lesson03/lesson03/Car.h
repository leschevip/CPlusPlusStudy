#pragma once

#include <string>
#include <iostream>

using namespace std;

class Car
{
private:
	string company;
	string model;

public:
	/*Car() : company(""), model("")
	{

	}*/

	Car(string company, string model) : company(company), model(model)
	{
		cout << __FUNCTION__ << endl;
	}

	virtual ~Car()
	{
		cout << __FUNCTION__ << endl;
	}
};


class PassengerCar : virtual public Car
{
public:
	PassengerCar(string company, string model) : Car(company, model)
	{
		cout << __FUNCTION__ << endl;
	}

	virtual ~PassengerCar()
	{
		cout << __FUNCTION__ << endl;
	}
};

class Bus : virtual public Car
{
public:
	Bus(string company, string model) : Car(company, model)
	{
		cout << __FUNCTION__ << endl;
	}

	virtual ~Bus()
	{
		cout << __FUNCTION__ << endl;
	}
};

class Minivan : public PassengerCar, public Bus
{
public:
	Minivan(string company, string model) : PassengerCar(company, model), Bus(company, model), Car(company, model)
	{
		cout << __FUNCTION__ << endl;
	}

	virtual ~Minivan()
	{
		cout << __FUNCTION__ << endl;
	}
};