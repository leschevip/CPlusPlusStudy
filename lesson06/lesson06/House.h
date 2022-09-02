#pragma once

#include "GenericPlayer.h"

class House : public GenericPlayer
{
	House(wstring& name) : GenericPlayer(name)
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