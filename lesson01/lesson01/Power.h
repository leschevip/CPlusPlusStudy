#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

using namespace std;

class Power
{

private:
	double val;
	double degree;

public:

	Power(double val = M_PI, double degree = M_E) : val(val), degree(degree)
	{

	}

	Power(Power &p)
	{
		this->val = p.val;
		this->degree = p.degree;
	}

	~Power()
	{

	}

	void set(double val, double degree)
	{
		this->val = val;
		this->degree = degree;
	}

	void calucate()
	{	
		cout << val << " ^ " << degree << " = " << pow(val, degree) << endl;
	}
};