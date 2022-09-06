#pragma once

#include <vector>
#include "Deck.h"
#include "Player.h"
#include "House.h"

using namespace std;


class Game
{
private:
	Deck deck;
	House house;
	vector<Player*> players;

public:
	Game(vector<string>& names) : house("diller")
	{	
		deck.Shuffle();
		for (string& name : names)
			players.push_back(new Player(name));
	}

	~Game()
	{
		for (Player* p : players)
			delete p;
		players.clear();
	}

	void Play()
	{
		deck.Deal(house);
		deck.Deal(house);
		house.FlipFirstCard();

		for (Player* p : players)
		{
			deck.Deal(*p);
			deck.Deal(*p);
			wcout << *p << endl;
		}
		wcout << house << endl;

		vector<Player*> playerEnds;
		while (players.size() != 0)
		{
			for (Player* p : players)
			{
				auto i = find(playerEnds.begin(), playerEnds.end(), p);
				if (i != playerEnds.end())
					continue;

				if (p->IsBoosted())
				{
					playerEnds.push_back(p);
				}
				else if (!p->IsHitting())
				{
					playerEnds.push_back(p);
				}
				else
				{
					deck.Deal(*p);
				}
			}

			if (playerEnds.size() == players.size())
				break;
		}

		cout << "Ok! All players made a choice!" << endl << endl;

		house.FlipFirstCard();

		while (house.IsHitting())
			deck.Deal(house);

		Player* pScore = players.at(0);
		bool isDraw = true;
		for (Player* p : players)
		{
			if (!p->IsBoosted())
				isDraw &= pScore->GetValue() == p->GetValue();
			if (!isDraw)
				break;
		}
		
		Player* pMaxScore = nullptr;
		if (!isDraw)
		{
			for (Player* p : players)
			{
				if (p->IsBoosted())
					continue;

				if (pMaxScore == nullptr)
				{
					pMaxScore = p;
				}
				else if (pMaxScore->GetValue() < p->GetValue())
				{
					pMaxScore = p;
				}
			}
		}

		wcout << house << endl << endl;
		for (Player* p : players)
			wcout << *p << endl << endl;

		for (Player* p : players)
		{
			if (p->IsBoosted())
				p->Bust();
			else if (isDraw)
				p->Push();
			else if (p != pMaxScore)
				p->Lose();
			else
				p->Win();
		}
		
	}

};