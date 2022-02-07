#pragma once
#include "Point.h";

class CRectangle
	{
	private:
		int _left;
		int _top;
		int _right;
		int _bottom;
	public:
		CRectangle()
			: _left(0), _right(0), _top(0), _bottom(0) { };
		
		CRectangle(const int left, const int top, const int right, const int bottom)
			: _left(left), _top(top), _right(right), _bottom(bottom) {};

		// width size in characters
		inline int Width() { return Right() - Left() + 1; };

		// height size in characters
		inline int Height() { return Bottom() - Top() + 1; };

		inline int Left() { return _left; };

		inline int Top() { return _top; };

		inline int Right() { return _right; };

		inline int Bottom() { return _bottom; };

		Point& LeftTop()
		{
			Point p(_left, _top);
			return p;
		}

		Point& RightBottom()
		{
			Point p(_right, _bottom);
			return p;
		}

		void NewSize(const int left, const int top, const int right, const int bottom)
		{
			_left += left;
			_top += top;
			_right += right;
			_bottom += bottom;
		}

		void NewSize(const Point& topLeft, const Point& rightBottom)
		{
			_left += topLeft.x;
			_top += topLeft.y;
			_right += rightBottom.x;
			_bottom += rightBottom.y;
		}

		/*
		void MoveBy(int nx, int ny) 
		{
			_left += nx;
			_top += ny;
			_right += nx;
			_bottom += ny;
		}*/

		bool PointIn(const Point& p)
		{
			return p.x >= _left && p.x <= _right && p.y >= _top && p.y <= _bottom;
		}

		bool PointIn(const int x, const int y)
		{
			return x >= _left && x <= _right && y >= _top && y <= _bottom;
		}

		bool XIn(const int x)
		{
			return x >= _left && x <= _right;
		}

		bool YIn(const int y)
		{
			return y >= _top && y <= _bottom;
		}
	};
