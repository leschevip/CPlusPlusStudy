#pragma once
#include "OutputArea.h"
#include "CRectangle.h";
#include <vector>

using namespace std;

class Perspective
{

private:
	CRectangle _rect;

	float _left;
	float _top;
	float _right;
	float _bottom;

	float _charW;
	float _charH;

	int _maxCharWCount;
	int _maxCharHCount;

	OutputArea* CreateOutputArea(AreaType type, float left, float top, float right, float bottom);

public:
	Perspective(CRectangle rect);
	~Perspective();
	float CharW();
	float CharH();
	int MaxCharWidthCount();
	int MaxCharHeightCount();

	OutputArea* Score;
	OutputArea* Game;
	OutputArea* Preview;
	OutputArea* Full;

};