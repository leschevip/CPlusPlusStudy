#pragma once
#include <string>

enum class Progress
{
	IN_PROGRESS,
	DRAW,
	HUMAN_WON,
	AI_WON
};

struct Position
{
	size_t y{ 0 };
	size_t x{ 0 };
};

struct Player
{
	std::string Name;
	char Chip;
};