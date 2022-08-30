#pragma once

#include <string>
#include <iostream>
#include "Hand.h"
#include "Input.h"

using namespace std;

class GenericPlayer : public Hand
{
private:
	string name;

public:
	GenericPlayer(string& name) : Hand(), name(name)
	{
	}
		
	virtual bool IsHitting()
	{
		cout << name << ", do you need one more card? \n 0 - No \n 1 - Yes\n";	
		return InputNumber<bool>(NAME_OF(answer));
	}

	bool IsBoosted()
	{
		return GetValue() > MAX_SCORE;
	}

	void Bust()
	{
		cout << name << "!" << " The Sum of your scores greater than " << MAX_SCORE;
	}
};