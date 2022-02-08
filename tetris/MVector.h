#pragma once

struct MVector
{
	int x;
	int y;

	MVector() : x(0), y(0) { }

	MVector(int nx, int ny) : x(nx), y(ny) { }
};