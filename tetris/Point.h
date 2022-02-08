#pragma once
#include "MVector.h"


struct Point
{
public:
	int x;
	int y;

	Point()
	{
		x = 0;
		y = 0;
	}

	Point(int nx, int ny)
	{ 
		x = nx; 
		y = ny; 
	}

	bool operator== (const Point& p)
	{
		return x == p.x && y == p.y;
	}

	Point& operator +=(const Point& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Point& operator +(const Point& v)
	{
		Point p(x + v.x, y + v.y);
		return p;
	}

	Point& operator +(const MVector& v)
	{
		Point p(x + v.x, y + v.y);
		return p;
	}

	Point& operator -(const Point& v)
	{
		Point p(x - v.x, y - v.y);
		return p;
	}

	Point& operator +=(MVector& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	bool operator < (const Point& r) const
	{
		return x < r.x && y < r.y;
	}

	bool operator > (const Point& r) const
	{
		return x > r.x && y > r.y;
	}
};