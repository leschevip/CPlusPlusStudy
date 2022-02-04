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
		
		CRectangle(int left, int top, int right, int bottom)
			: _left(left), _top(top), _right(right), _bottom(bottom) {};

		// width size in characters
		inline int Width() { return Right() - Left() + 1; };

		// height size in characters
		inline int Height() { return Bottom() - Top() + 1; };

		inline int Left() { return _left; };

		inline int Top() { return _top; };

		inline int Right() { return _right; };

		inline int Bottom() { return _bottom; };

		Point LeftTop() { return Point(_left, _top); }

		Point RightBottom() { return Point(_right, _bottom); }

		void MoveBy(int nx, int ny) 
		{
			_left += nx;
			_top += ny;
			_right += nx;
			_bottom += ny;
		}

		bool In(Point& p)
		{
			return p.x >= _left && p.x <= _right && p.y >= _top && p.y <= _bottom;
		}
	};
