#include "game.h"

Game::Game(GameView* const view, Data* const data) : _data(data), _view(view)
{
}

void Game::InitGame()
{
	_data->SetAreaSize(_view->GetAreaSize());
	_data->SetPlayersQuantity(_view->GetQuantityPlayers());
	
	auto *players = _data->Players();
	for (size_t i = 0; i < _data->PlayersQuantity(); i++)
	{
		Player* player = _view->InputPlayerData();
		players->push_back(player);
	}
	_data->SetActivePlayer(input::GetRandomNum(0, players->size() - 1));
}

void Game::DeInitGame()
{
	delete _data;
	_data = nullptr;

	delete _view;
	_view = nullptr;
}

void Game::PrintAll()
{
	_view->PrintAll();
}

void Game::Progress()
{
	do
	{
		_view->PrintAll();
		
		auto* player = _data->ActivePlayer();
		auto pos = _data->CurrentPosition();
		if (!player->IsAI)
		{
			while (true)
			{
				Position direction;
				bool isChoice = _view->MoveCursorChoice(direction);
				if (!isChoice)
				{
					pos = NextFreePosition(pos, direction);
					_data->SetCurrentPosition(pos);
					_view->PrintAll();
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			pos = GetAiInput(player);
		}
		_data->AppyUserChoice(pos);
		_data->SetProgressState(GetGameState());
	}
	while (_data->IsProgress());
	_view->Congrats();
}

Position Game::GetAiInput(const Player* const player)
{
	auto area = _data->Area();

	// предвыигрышные ситуации
	for (int32_t y = 0; y < _data->Size(); y++)
	{
		for (int32_t x = 0; x < _data->Size(); x++)
		{
			if (area[y][x] == _data->EMPTYCHAR)
			{
				area[y][x] = player->Chip;
				auto state = GetGameState();
				if (state.ProgressGame == Progress::AI_WON)
				{
					area[y][x] = _data->EMPTYCHAR;
					return { y,x };
				}
				area[y][x] = _data->EMPTYCHAR;
			}
		}
	}

	// предпроигрышные ситуации
	for (int32_t y = 0; y < _data->Size(); y++)
	{
		for (int32_t x = 0; x < _data->Size(); x++)
		{
			if (area[y][x] == _data->EMPTYCHAR)
			{
				area[y][x] = player->Chip;
				auto state = GetGameState();
				if (state.ProgressGame == Progress::HUMAN_WON)
				{
					area[y][x] = _data->EMPTYCHAR;
					return { y,x };
				}
				area[y][x] = _data->EMPTYCHAR;
			}
		}
	}

	vector<Position> positions;
	size_t num(0);
	for (int32_t y = 0; y < _data->Size(); y++)
	{
		for (int32_t x = 0; x < _data->Size(); x++)
		{
			if (area[y][x] == _data->EMPTYCHAR)
			{
				positions.push_back({ y,x });
				num++;
			}
		}
	}

	if (num > 0)
	{
		const size_t index = input::GetRandomNum(0, num - 1);
		return positions[index];
	}

	throw;
}

Position Game::NextFreePosition(const Position& current, const Position& v)
{
	auto area = _data->Area();
	if (v.x == 0 && v.y == 0)
		return current;

	int32_t sign(0);
	Position next{ current.y + v.y, current.x + v.x };

	if (v.x != 0 && v.y == 0)
	{
		sign = v.x > 0 ? 1 : -1;
		if (next.x < 0 || next.x == _data->Size())
			return current;

		while (area[next.y][next.x] != _data->EMPTYCHAR)
		{
			if (next.x > 0 && next.x < _data->Size())
				next.x += sign;
			else
				return current;
		}
	}
	else if (v.y != 0 && v.x == 0)
	{
		if (next.y < 0 || next.y == _data->Size())
			return current;
		sign = v.y > 0 ? 1 : -1;
		while (area[next.y][next.x] != _data->EMPTYCHAR)
		{
			if (next.y > 0 && next.y < _data->Size())
				next.y += sign;
			else
				return current;
		}
	}
	else
		throw;

	return next;
}

State Game::GetGameState()
{
	auto* area = _data->Area();

	bool draw(true);
	for (size_t y = 0; y < _data->Size(); y++)
	{
		for (size_t x = 0; x < _data->Size(); x++)
		{
			if (area[y][x] == _data->EMPTYCHAR)
			{
				draw = false;
				break;
			}
		}
		if (!draw)
			break;
	}

	if (draw)
	{
		return { Progress::DRAW, nullptr };
	}
	else
	{
		for (auto* player : *_data->Players())
		{
			// by rows
			for (size_t y = 0; y < _data->Size(); y++)
			{
				size_t count(0);

				for (size_t x = 0; x < _data->Size(); x++)
				{
					if (area[y][x] == player->Chip)
						count++;
				}

				if (count == _data->Size())
				{
					return { player->IsAI ? Progress::AI_WON : Progress::HUMAN_WON, player };
				}
			}

			// by columns
			for (size_t x = 0; x < _data->Size(); x++)
			{
				size_t count(0);

				for (size_t y = 0; y < _data->Size(); y++)
				{
					if (area[y][x] == player->Chip)
						count++;
				}

				if (count == _data->Size())
				{
					return { player->IsAI ? Progress::AI_WON : Progress::HUMAN_WON, player };
				}
			}

			// by diags
			size_t count(0);
			for (size_t y = 0; y < _data->Size(); y++)
			{

				if (area[y][y] == player->Chip)
					count++;
			}
			if (count == _data->Size())
			{
				return { player->IsAI ? Progress::AI_WON : Progress::HUMAN_WON, player };
			}

			count = 0;
			size_t lastIdx = _data->Size() - 1;
			for (size_t y = 0; y < _data->Size(); y++)
			{

				if (area[lastIdx - y][y] == player->Chip)
					count++;
			}
			if (count == _data->Size())
			{
				return { player->IsAI ? Progress::AI_WON : Progress::HUMAN_WON, player };
			}
		}
	}
	return { Progress::IN_PROGRESS, nullptr };

}
