#pragma once
#include "CRectangle.h"

enum class AreaType
{
	EMPTY,
	SCORE,
	GAME,
	PREVIEW,
	SCREEN
};

class OutputArea
{
private:
	CRectangle _bounds;
	CRectangle _area;
	AreaType _type;
public:
	// area bounds
	CRectangle& Bounds() { return _bounds; };
	// client part output
	CRectangle& ClientPart() { return _area; };
	// type
	AreaType Type() { return _type; }

	bool IsType(AreaType type) { return _type == type; };

	OutputArea()
		: _bounds(CRectangle()), _area(CRectangle()), _type(AreaType::EMPTY) { };

	OutputArea(AreaType type)
		: _bounds(CRectangle()), _area(CRectangle()), _type(type) { };

	OutputArea(AreaType type, CRectangle rect)
		: _bounds(rect), _area(rect.Left() + 1, rect.Top() + 1, rect.Right() - 1, rect.Bottom() - 1), _type(type) { };

};
