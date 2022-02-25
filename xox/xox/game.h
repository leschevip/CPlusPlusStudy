#pragma once
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <math.h>
#include "gameview.h"

using namespace std;

class Game
{
private:
	Data* _data;
	GameView* _view;
	Position GetAiInput(const Player * const player);
	Position NextFreePosition(const Position& current, const Position& v);
	State GetGameState();
	AiInfo AnalizeVector(vector<Position> playerPositions, const Player* const player, function<char(Position, size_t)> valueGetter);
	size_t GetDiagCounts(const size_t shift, const Player* const player, function<char(size_t, size_t)> valueGetter);
public:
	Game(GameView* const view, Data* const data);
	void InitGame();
	~Game();
	void PrintAll();
	void Progress();
};