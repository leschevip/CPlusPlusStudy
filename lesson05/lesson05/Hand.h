#pragma once

#include <vector>
#include <algorithm>
#include "Card.h"
#include "BlackJackConst.h"

using namespace std;

class Hand
{
private:
	vector<Card*> list;

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
		list.push_back(c);
	}

	void Clear()
	{
		list.clear();
		// деструктор карт на руке не вызываем здесь. будем это делать в деструкторе колоды
	}

	int GetValue()
	{
		int sum = 0;

		sort(begin(list), end(list),
			[](Card* a, Card* b)
			{
				return a->GetValue() > b->GetValue();
			});

		for (size_t i = 0; i < list.size(); i++)
		{
			Card* c = list.at(i);
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
	}
};