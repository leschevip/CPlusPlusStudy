#pragma once
#include "Point.h"
#include "CRectangle.h"
#include <vector>

using namespace std;

struct FigurePositionData
{
	double Angle;
	Point pos;
	vector<Point> NewPoints;
	CRectangle NewBounds;
	bool IsIntersect;

	~FigurePositionData()
	{
		NewPoints.clear();
	}
};