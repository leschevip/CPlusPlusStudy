#include "game.h"

Game::Game() : _size(0), _area(nullptr)
{
}

void Game::InitGame(GameView& view)
{
	_size = view.GetAreaSize();
	_area = new char*[_size];
	for (size_t i = 0; i < _size; i++)
		_area[i] = new char[_size];

	size_t players{ 0 };
	do
	{
		players = view.GetQuantityPlayers();
		if (players > MAX_PLAYERS_COUNT)
			view.Print("Players count can't be greater than " + to_string(MAX_PLAYERS_COUNT));
	} 
	while (players > MAX_PLAYERS_COUNT);

	const char chips[] = { '#', '$', '%', '0', 'X' };

	for (size_t i = 0; i < players; i++)
	{
		Player player;
		player.Name = view.GetPlayerName();
		bool isAvailableChip{ true };
		do
		{
			auto chip = view.GetChip();
			isAvailableChip = find_if(_players.begin(), _players.end(), [&](Player p) { return p.Chip == chip; }) == _players.end();
			if (!isAvailableChip)
				view.Print("Input other chip, please");
			else
				player.Chip = chip;
		} 
		while (!isAvailableChip);

		_players.push_back(player);
	}

}