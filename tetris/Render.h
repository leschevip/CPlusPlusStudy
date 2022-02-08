#include "Perspective.h"
#include "GameData.h"
#include <curses.h>
//#include <iostream>
#include <string>

using namespace std;

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
	
	Render(Perspective* const p, GameData* const data);
	~Render();
	int Rendering();
	//int RenderingEndGame();
};