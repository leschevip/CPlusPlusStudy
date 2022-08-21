#pragma once

#include <string>
#include "Apple.h"

class GrannySmith : public Apple
{
public:
	GrannySmith(const string& color = "green")
		: Apple(color)
	{
		name = "Granny Smith " + Apple::name;
	}
};