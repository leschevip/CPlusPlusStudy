#pragma once

#define PI 3.14

#include <math.h>
#include <iostream>

using namespace std;

class Figure
{
public: 
	virtual double area() const = 0;
};

class Parallelogram : public Figure
{
protected:
	double a;
	double b;
	double angle;

public:

	Parallelogram() : a(0), b(0), angle(0)
	{

	}

	Parallelogram(double a, double b, double angle) : a(a), b(b), angle(angle)
	{
	}

	virtual double area() const override
	{
		return a * b * sin(angle * PI / 180);
	}
};

class Circle : public Figure
{
private:
	double r;

public:
	Circle(double r) : r(r)
	{
	}

	virtual double area() const override
	{
		return PI * r * r;
	}
};

class Rectangle : public Parallelogram
{
public:
	Rectangle(double a, double b) : Parallelogram(a, b, 90)
	{

	}

	virtual double area() const override
	{
		return a * b;
	}
};

class Square : public Parallelogram
{
public:
	Square(double a) : Parallelogram(a, a, 90)
	{

	}

	virtual double area() const override
	{
		return a * b;
	}
};

class Rhombus : public Parallelogram
{
private:
	double diagh;
	double diagv;

public:
	Rhombus(double diagh, double diagv)
		: diagh(diagh), diagv(diagv), Parallelogram()
	{
		a = sqrt(diagh * diagh / 4 + diagv * diagv / 4);
		b = a;
		angle = asin(diagh / 2 / a);
	}

	virtual double area() const override
	{
		return diagh * diagv / 2;
	}
};

void printFigure(const Figure* f);