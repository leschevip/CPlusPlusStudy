#pragma once
#include <string>
#include <vector>
#include "gameview.h"

using namespace std;

enum class Progress
{
	IN_PROGRESS,
	DRAW,
	HUMAN_WON,
	AI_WON
};

enum class Figure
{
	CROSS = 'X',
	ZERO = '0',
	EMPTY = ' '
};

struct Position
{
	size_t y{ 0 };
	size_t x{ 0 };
};

struct Player
{
	string Name;
	Figure Chip;
};

class Game
{
private:
	vector<Player> players;

public:
	Game();
	void InitGame(const GameView& view);
	void AddPlayer(const Player& player);
};