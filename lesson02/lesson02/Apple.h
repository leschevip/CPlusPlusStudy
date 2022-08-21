#pragma once

#include <string>
#include "Fruit.h"

class Apple : public Fruit
{
public:
	Apple(const string& color) : Fruit("apple", color)
	{

	}
};