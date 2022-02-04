#pragma once
#include "CRectangle.h"
#include <vector>
#include <functional>
#include "common.h"

using namespace std;

enum class FigureType
{
	F1,
	F2
};

class Figure
{
public:
	vector<Point> Points;
	CRectangle Size;
	Figure();
	~Figure();
};

class FigureInstance
{
public:
	Figure* Model;
	vector<Point> Points;
	CRectangle* Size;
	Point* Position;
	FigureInstance();
	FigureInstance(Figure *model, vector<Point>& points);
	~FigureInstance();
};

struct FigureLocation
{
	int Index;
	float Angle;
	int X;
	int Y;
	bool IsInitialized;
};