#include "Figure.h"

vector<Point>* Figure::Points()
{
	return _points;
}

CRectangle& Figure::Size()
{
	return GetVectorPointsBounds(*_points);
}

Figure::Figure()
{
	_points = new vector<Point>();
}

Figure::~Figure()
{
	(*_points).clear();
}

FigureInstance::FigureInstance(): _model(nullptr), _posCS(nullptr), _curPoints(nullptr), _angle(0.0f)
{
	_curPoints = new vector<Point>();
}

FigureInstance::FigureInstance(Figure* model, Point* posLcs) 
	: _model(model), _angle(0.0f)
{
	SetPosCS(*posLcs);
	_curPoints = new vector<Point>();
}


FigureInstance::~FigureInstance()
{
	delete _posCS;
	_posCS = nullptr;
	_model = nullptr;
	
	_curPoints->clear();
	_curPoints = nullptr;
}

Point* FigureInstance::PosCS()
{
	return _posCS;
}

double FigureInstance::Angle()
{
	return _angle;
}

Figure* FigureInstance::Model()
{
	return _model;
}

CRectangle& FigureInstance::Bounds()
{
	return _bounds;
}

void FigureInstance::SetData(FigurePositionData data)
{
	SetPosCS(data.pos);
	SetAngle(data.Angle);
	SetPoints(data.NewPoints);
	SetBounds(data.NewBounds);
}

void FigureInstance::SetPosCS(const Point& pos)
{
	if (_posCS == nullptr)
		_posCS = new Point(pos.x, pos.y);
	else
	{
		_posCS->x = pos.x;
		_posCS->y = pos.y;
	}
}

void FigureInstance::SetAngle(const double angle)
{
	_angle = angle;
}

void FigureInstance::SetPoints(const vector<Point>& points)
{
	_curPoints->clear();
	for (auto point : points)
		_curPoints->push_back(point);
}

void FigureInstance::SetBounds(const CRectangle& bounds)
{
	_bounds = bounds;
}

vector<Point>* FigureInstance::Points()
{
	return _curPoints;
}