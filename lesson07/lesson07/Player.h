#pragma once

#include <string>
#include <iostream>
#include "Hand.h"
#include "GenericPlayer.h"

using namespace std;

class Player : public GenericPlayer
{
public:
	Player(string& name) : GenericPlayer(name)
	{
	}

	~Player()
	{
	}

	bool IsHitting() override
	{
		return GenericPlayer::IsHitting();
	}

	void Win() const
	{
		wcout << name << "! You are win!" << endl;
	}

	void Lose() const
	{
		wcout << name << "! You are lose :(" << endl;
	}

	void Push() const
	{
		wcout << name << "! The game ended in a draw!" << endl;
	}
};