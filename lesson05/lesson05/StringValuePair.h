#pragma once

#include "Pair.h"
#include <string>

using namespace std;

template<typename T = int>
class StringValuePair : public Pair<string, T>
{
public:

	StringValuePair(string key, T val) : Pair<string, T>(key, val)
	{

	}
};