#include "Perspective.h"
#include "GameData.h"
#include <curses.h>
#include <string>


class Render
{
private:	
	GameData* _data;
public:
	Render(GameData* data);
	~Render();
	int Rendering();
};