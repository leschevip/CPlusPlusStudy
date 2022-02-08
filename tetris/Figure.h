#pragma once
#include "CRectangle.h"
#include <vector>
#include <functional>
#include "common.h"
#include "FigurePositionData.h"

using namespace std;

enum class FigureType
{
	F1,
	F2
};

class Figure
{
private:
	vector<Point>* _points;
public:
	vector<Point>* Points();
	CRectangle& Size();
	Figure();
	~Figure();
};

class FigureInstance
{
private:
	Figure* _model;
	Point* _posCS;
	double _angle;
	vector<Point>* _curPoints;
	CRectangle _bounds;

	void SetPosCS(const Point& pos);
	void SetAngle(const double& angle);
	void SetPoints(const vector<Point>& points);
	void SetBounds(const CRectangle& bounds);

public:
	FigureInstance();
	FigureInstance(Figure * const model, Point* const posLcs);
	~FigureInstance();
	Point* PosCS();
	double Angle();
	vector<Point>* Points();
	Figure* Model();
	CRectangle& Bounds();
	void SetData(const FigurePositionData& data);
};

