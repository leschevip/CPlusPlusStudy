#include "ConsoleView.h"

ConsoleView::ConsoleView(Data* const data) : GameView(data)
{

}

void ConsoleView::PrintAll()
{
	system("cls");

	Position pos = _data->CurrentPosition();
	auto state = _data->State();
	
	cout << "     ";
	for (size_t x = 0; x < _data->Size(); x++)
	{
		cout << x + 1 << "   ";
	}
	cout << endl;

	auto* area = _data->Area();
	for (size_t y = 0; y < _data->Size(); y++)
	{
		cout << " " << y + 1 << " | ";

		for (size_t x = 0; x < _data->Size(); x++)
		{
			char ch(0);
			if (state.ProgressGame == Progress::IN_PROGRESS)
			{
				ch = pos.x == x && pos.y == y ? _data->ActivePlayer()->Chip : area[y][x];
			}
			else
			{
				ch = area[y][x];
			}
			cout << ch << " | ";
		}
		cout << endl;
	}

	cout << endl;
	auto* players = _data->Players();
	for (auto *p : *players)
	{
		cout << p->Name << ": " << p->Chip << endl;
	}

	if (state.ProgressGame == Progress::DRAW)
	{
		cout << "It's draw!";
	}
	else if (state.ProgressGame != Progress::IN_PROGRESS)
	{
		cout << "Win a" << (state.ProgressGame == Progress::HUMAN_WON ? " human " : " computer ") << state.Winner->Name;
	}
}

Player* ConsoleView::InputPlayerData()
{
	Player* player = new Player();
	cout << "New player:" << endl;
	player->Name = input::InputString("player name");
	player->IsAI = input::InputNumber<bool>("is player AI (0 / 1)");

	auto* players = _data->Players();
	bool isAvailableChip{ true };
	do
	{
		player->Chip = input::InputNumber<char>("player chip");
		isAvailableChip = find_if(players->begin(), players->end(), [&](Player* p) { return p->Chip == player->Chip; }) == players->end();
		if (!isAvailableChip)
			cout << "Input other chip, please" << endl;
	} 
	while (!isAvailableChip);
	return player;
}

size_t ConsoleView::GetAreaSize()
{
	return input::InputNumber<size_t>("area size");;
}

size_t ConsoleView::GetQuantityPlayers()
{
	size_t playersCount{ 0 };
	do
	{
		playersCount = input::InputNumber<size_t>("player quantity");
		if (playersCount > _data->Size())
			cout << "Players count can't be greater than " + to_string(_data->Size());
	} while (playersCount > _data->Size());
	return playersCount;
}

bool ConsoleView::MoveCursorChoice(OUT Position& v)
{

	int key = _getch();
	if (key != ENTER)
		key = _getch();

	switch (key)
	{
	case UP:
		v.y = -1;
		break;
	case DOWN:
		v.y = 1;
		break;
	case LEFT:
		v.x = -1;
		break;
	case RIGHT:
		v.x = 1;
		break;
	case ENTER:
		return true;
		break;
	default:
		break;
	}
	
	return false;
}