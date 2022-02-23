#pragma once
#include <string>
#include "input.h"
#include "data.h"

class GameView
{
public:
	virtual void Print(string message) = 0;
	virtual string GetPlayerName() = 0;
	virtual char GetChip() = 0;
	virtual size_t GetAreaSize() = 0;
	virtual size_t GetQuantityPlayers() = 0;
};