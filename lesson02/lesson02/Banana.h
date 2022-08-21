#pragma once

#include <string>
#include "Fruit.h"

class Banana : public Fruit
{
public:
	Banana(const string& name = "banana", const string& color = "yellow")
		: Fruit(name, color)
	{

	}
};