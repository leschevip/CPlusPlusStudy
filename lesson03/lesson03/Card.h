#pragma once

enum CardSuit
{
	kresti,
	chervi,
	bubi,
	piki
};

class Card
{
private:
	CardSuit suit;
	int value;
	bool position;
public:
	void Flip()
	{
		position = !position;
	}

	int GetValue()
	{
		return value;
	}
};