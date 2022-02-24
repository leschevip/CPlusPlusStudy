#pragma once
#include <string>
#include <vector>
#include <random>
#include <chrono>
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
public:
	Game(GameView* const view, Data* const data);
	void InitGame();
	void DeInitGame();
	void PrintAll();
	void Progress();
};