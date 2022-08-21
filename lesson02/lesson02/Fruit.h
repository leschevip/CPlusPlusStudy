#pragma once

#include <string>

using namespace std;

class Fruit
{
protected:
	string name;
	string color;

public:
	Fruit(const string& name, const string& color) : name(name), color(color)
	{

	}

	string& getColor()
	{
		return color;
	}

	string& getName()
	{
		return name;
	}

};