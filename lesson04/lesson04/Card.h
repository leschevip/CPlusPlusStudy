#pragma once

enum CardSuit
{
	kresti,
	chervi,
	bubi,
	piki
};

enum CardType
{
	Number,
	Ace,
	King,
	Lady,
	Jack
};



class Card
{
private:
	CardSuit suit;
	CardType type;
	int value;
	bool position;
public:
	
	Card() = delete;

	Card(CardSuit suit, CardType type, int value) : suit(suit), type(type), value(value), position(false)
	{

	}

	void Flip()
	{
		position = !position;
	}

	CardType GetType()
	{
		return type;
	}

	int GetValue()
	{
		return value;
	}


};