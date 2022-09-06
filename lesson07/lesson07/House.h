#pragma once

#include "GenericPlayer.h"

class House : public GenericPlayer
{

public:
	House(string name) : GenericPlayer(name)
	{
	}

	~House()
	{
	}

	bool IsHitting() override
	{
		return Hand::GetValue() < MAX_HOUSE_SCORE;
	}

	void FlipFirstCard()
	{
		if (cards.size() > 0)
		{
			cards.at(0)->Flip();
		}
	}
};