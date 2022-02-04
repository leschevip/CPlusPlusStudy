#pragma once
#include "Point.h"

struct TSymbol
{
	Point point;
	char code;

	TSymbol() : point(Point()), code(0) {}
	TSymbol(int nx, int ny, char c) : point(Point(nx, ny)), code(c) { }
};