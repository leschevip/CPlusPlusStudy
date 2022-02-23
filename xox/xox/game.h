#pragma once
#include <string>
#include <vector>
#include "gameview.h"

using namespace std;

class Game
{
private:
	vector<Player> _players;
	size_t _size;
	char** _area;
public:
	const size_t MAX_PLAYERS_COUNT = 5;

	Game();
	void InitGame(GameView& view);
};