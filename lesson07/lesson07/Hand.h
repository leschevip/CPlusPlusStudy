#pragma once

#include <vector>
#include <algorithm>
#include "Card.h"
#include "BlackJackConst.h"

using namespace std;

class Hand
{
protected:
	vector<Card*> cards;

public:
	
	Hand() 
	{
	}
	
	virtual ~Hand()
	{
		Clear();
	}

	void Add(Card* c)
	{
		cards.push_back(c);
	}

	void Clear()
	{
		for (Card* c : cards)
			delete c;
		cards.clear();
	}

	int GetValue()
	{
		int sum = 0;

		sort(begin(cards), end(cards),
			[](Card* a, Card* b)
			{
				return a->GetValue() > b->GetValue();
			});

		for (size_t i = 0; i < cards.size(); i++)
		{
			Card* c = cards.at(i);
			int v = c->GetValue();
			int sumTmp = sum + v;

			if (c->GetType() == CardType::Ace && sumTmp > MAX_SCORE)
			{
				sum += MIN_SCORE_VALUE;
			}
			else 
			{
				sum += v;
			}
		}

		return sum;
	}
};