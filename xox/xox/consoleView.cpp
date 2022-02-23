#include "ConsoleView.h"

ConsoleView::ConsoleView()
{

}

void ConsoleView::Print(string message)
{
	cout << message << endl;
}

string ConsoleView::GetPlayerName()
{
	return input::InputString("player name");;
}

char ConsoleView::GetChip()
{
	return input::InputNumber<char>("player chip");
}

size_t ConsoleView::GetAreaSize()
{
	return input::InputNumber<size_t>("area size");;
}

size_t ConsoleView::GetQuantityPlayers()
{
	return input::InputNumber<size_t>("player quantity");;
}