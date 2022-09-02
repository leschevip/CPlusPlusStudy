#pragma once

#include <iostream>
#include "BlackJackConst.h"
#include <fcntl.h>
#include <io.h>

enum CardSuit
{
	clubs,
	diamonds,
	hearts, 
	spades
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
	unsigned char value;
	bool isFlipped;

	ColorCode color;
	wstring character;
	wstring symbol;
public:
	
	Card() = delete;

	Card(CardSuit suit, CardType type, unsigned char value) 
		: suit(suit), type(type), value(value), isFlipped(false), color(ColorCode::FG_DEFAULT)
	{
		switch (suit)
		{
		case clubs:
			color = ColorCode::FG_YELLOW;
			character = L"♣";
			break;
		case diamonds:
			color = ColorCode::FG_GREEN;
			character = L"♦";
			break;
		case hearts:
			color = ColorCode::FG_RED;
			character = L"♥";
			break;
		case spades:
			color = ColorCode::FG_BLUE;
			character = L"♠";
			break;
		default:
			break;
		}

		switch (type)
		{
		case Number:
			symbol = to_wstring(value);
			break;
		case Ace:
			symbol = L"A";
			break;
		case King:
			symbol = L"K";
			break;
		case Lady:
			symbol = L"L";
			break;
		case Jack:
			symbol = L"J";
			break;
		default:
			break;
		}
	}

	void Flip()
	{
		isFlipped = !isFlipped;
	}

	CardType GetType()
	{
		return type;
	}

	int GetValue()
	{
		return value;
	}

	friend wostream& operator<<(wostream& in, Card& card)
	{
		if (card.isFlipped)
		{
			in << "XX";
		}
		else
		{
			_setmode(_fileno(stdout), _O_U16TEXT);
			in << "\033[" << card.color << "m";
			in << card.symbol << card.character;
			in << "\033[" << ColorCode::FG_DEFAULT << "m";
			_setmode(_fileno(stdout), _O_TEXT);

			// Also we can do like this
			// https://blogs.msmvps.com/gdicanio/tag/unicode/
		}
		return in;
	}
};