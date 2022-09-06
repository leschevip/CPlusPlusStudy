#pragma once

#include "Hand.h"
#include "GenericPlayer.h"

using namespace std;

class Deck : public Hand
{
private:

	void Populate()
	{
		for (int s = 0; s <= CardSuit::length - 1; s++)
		{
			for (int i = 1; i <= 10; i++)
				cards.push_back(new Card((CardSuit)s, CardType::Number, i));

			cards.push_back(new Card((CardSuit)s, CardType::Ace, ACE_SCORE));
			cards.push_back(new Card((CardSuit)s, CardType::King, KING_SCORE));
			cards.push_back(new Card((CardSuit)s, CardType::Lady, LADY_SCORE));
			cards.push_back(new Card((CardSuit)s, CardType::Jack, JACK_SCORE));
		}
	}

	
public:
	Deck()
	{
		Populate();
	}

	~Deck() 
	{
	}

	void Deal(Hand& hand)
	{
		hand.Add(*(cards.end() - 1));
		cards.erase(cards.end() - 1);
	}

	void AddltionalCards(GenericPlayer& player)
	{
		if (player.IsHitting())
			Deal(player);
	}

	void Shuffle()
	{
		random_shuffle(cards.begin(), cards.end());
	}

};