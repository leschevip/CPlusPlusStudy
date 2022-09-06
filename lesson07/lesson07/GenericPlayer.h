#pragma once

#include <string>
#include <iostream>
#include "Hand.h"
#include "Input.h"

using namespace std;

class GenericPlayer : public Hand
{
protected:
	wstring name;

public:
	GenericPlayer(string& name) : Hand(), name(name.begin(), name.end())
	{
	}

	~GenericPlayer()
	{
	}
		
	virtual bool IsHitting()
	{
		wcout << name << ", do you need one more card? \n 0 - No \n 1 - Yes\n";
		return Input<bool>(NAME_OF(answer));
	}

	bool IsBoosted()
	{
		return GetValue() > MAX_SCORE;
	}

	void Bust()
	{
		wcout << name << "!" << " The Sum of your scores greater than " << MAX_SCORE;
	}

	friend wostream& operator<<(wostream& in, GenericPlayer& player)
	{
		_setmode(_fileno(stdout), _O_U16TEXT);
		in << player.name << ":\nHand: ";
		for (Card* c : player.cards)
			in << *c << "  ";
		in << endl;
		in << "Score: " << player.GetValue();
		_setmode(_fileno(stdout), _O_TEXT);
		return in;
	}
};