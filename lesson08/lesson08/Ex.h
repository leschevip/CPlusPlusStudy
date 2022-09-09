#pragma once

using namespace std;

class Ex
{
private:
	double x;
public:
	Ex(double xx) : x(xx)
	{
	}

	double what()
	{
		return x;
	}
};

class Bar
{
private:
	double y;
public:
	Bar() : y(0) {}
	void Set(double a)
	{
		if (y + a > 100)
			throw Ex(y * a);
		else
			y += a;
	}
};
