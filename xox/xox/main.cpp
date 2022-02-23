#include "consoleView.h"
#include "GameView.h"
#include "game.h"


int main()
{
	ConsoleView view;
	Game g;
	g.InitGame((GameView&)view);
	return 0;
}