#pragma once
#include <string>
#include <iostream>
#include "GameView.h"

class ConsoleView : GameView
{
public:
	ConsoleView();
	void Print(string message) override;
	string GetPlayerName() override;
	char GetChip() override;
	size_t GetAreaSize() override;
	size_t GetQuantityPlayers() override;
};