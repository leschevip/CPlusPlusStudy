#pragma once
#include "OutputArea.h"
#include "CRectangle.h";
#include <vector>

using namespace std;


class Perspective
{

private:
	CRectangle _rect;

	

	float _charW;
	float _charH;

	uint32_t _maxCharWCount;
	uint32_t _maxCharHCount;

	OutputArea* CreateOutputArea(const AreaType& type, const float& left, const float& top, const float& right, const float& bottom);

public:
	Perspective(const CRectangle& rect);
	~Perspective();
	float CharW();
	float CharH();
	uint32_t MaxCharWidthCount();
	uint32_t MaxCharHeightCount();
	OutputArea* Output(const AreaType& type);

	OutputArea* Score;
	OutputArea* Game;
	OutputArea* Preview;
	OutputArea* Full;

};