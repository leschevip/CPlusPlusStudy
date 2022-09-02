#pragma once

#include <string>
#include <iostream>
#include "Hand.h"
#include "GenericPlayer.h"
#include "Input.h"

using namespace std;

class Player : public GenericPlayer
{
public:
	Player(wstring& name) : GenericPlayer(name)
	{
	}

	bool IsHitting() override
	{
		return GenericPlayer::IsHitting();
	}

	void Win() const
	{
		wcout << name << "! You are win!";
	}

	void Lose() const
	{
		wcout << name << "! You are lose :(";
	}

	void Push() const
	{
		wcout << name << "! The game ended in a draw!";
	}
};