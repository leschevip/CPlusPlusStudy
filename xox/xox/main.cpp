#include "consoleView.h"
#include "GameView.h"
#include "game.h"


int main()
{
	Data* data = new Data();
	ConsoleView* view = new ConsoleView(data);
	Game g((GameView*)view, data);
	g.InitGame();
	g.Progress();
	return 0;
}