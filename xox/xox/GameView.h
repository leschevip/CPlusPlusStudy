#pragma once
#include <string>
#include "input.h"
#include "data.h"

class GameView
{
protected:
	Data* _data;
public:
	GameView(Data* const data) : _data(data) { }
	virtual void PrintAll() = 0;
	virtual Player* InputPlayerData() = 0;
	virtual size_t GetAreaSize() = 0;
	virtual size_t GetQuantityPlayers() = 0;
	virtual bool MoveCursorChoice(OUT Position& v) = 0;
	virtual void Congrats() = 0;
};