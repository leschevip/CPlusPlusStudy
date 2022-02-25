#pragma once
#include <string>
#include <iostream>
#include <conio.h>
#include "GameView.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13

class ConsoleView : GameView
{
public:
	ConsoleView(Data* const data);
	void PrintAll() override;
	Player* InputPlayerData() override;
	size_t GetAreaSize() override;
	size_t GetQuantityPlayers() override;
	bool MoveCursorChoice(OUT Position& v) override;
};