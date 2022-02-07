#include "Perspective.h"
#include "GameData.h"
#include <curses.h>
//#include <iostream>
#include <string>


class Render
{
private:	
	char** _frame;
	Perspective* _p;
	GameData* _data;

	void initFrame();
	void initFrameStatic(CRectangle& rect);
	void clearFrame(CRectangle& rect);
public:
	static const const char C_EMPTY_CHAR = ' ';
	static const const char C_BOUNDS_CHAR = '#';
	Render(Perspective* const p, GameData* const data);
	~Render();
	int Rendering();
};