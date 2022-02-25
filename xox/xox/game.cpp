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

Game::~Game()
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

Position Game::AnalizeVector(vector<Position> playerPositions, const Player* const player, function<char(Position, size_t)> valueGetter)
{
	struct info { Position pos; int32_t count; };
	vector<info> data;

	for (auto pos : playerPositions)
	{
		int32_t index(-1);
		for (size_t idx = 0; idx < _data->Size(); idx++)
		{
			if (valueGetter(pos, idx) != player->Chip)
			{
				index = idx;
				break;
			}
		}

		if (index != -1)
		{
			bool isSkip(false);
			for (size_t idx = 0; idx < _data->Size(); idx++)
			{
				auto chip = valueGetter(pos, idx);
				if (chip != player->Chip && chip != _data->EMPTYCHAR)
				{
					isSkip = true;
					break;
				}
			}

			if (!isSkip)
			{
				int32_t count(0);
				for (size_t idx = 0; idx < _data->Size(); idx++)
				{
					if (valueGetter(pos, idx) == player->Chip)
						count++;
				}

				data.push_back({ pos, count });
			}
		}
	}

	if (data.size() > 0)
	{
		info maxitem = data.at(0);
		for (auto item : data)
		{
			if (maxitem.count < item.count)
				maxitem = item;
		}

		return maxitem.pos;
	}
	else
		return {-1, -1};

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
				for (auto p : *_data->Players())
				{
					if (p->Chip != player->Chip)
					{
						area[y][x] = p->Chip;
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
		}
	}

	// предпроигрышные ситуации
	for (int32_t y = 0; y < _data->Size(); y++)
	{
		for (int32_t x = 0; x < _data->Size(); x++)
		{
			if (area[y][x] == _data->EMPTYCHAR)
			{
				for (auto p : *_data->Players())
				{
					if (p->Chip != player->Chip)
					{
						area[y][x] = p->Chip;
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
		}
	}

	vector<Position> positions;
	vector<Position> playerPositions;
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

			if (area[y][x] == player->Chip)
			{
				playerPositions.push_back({ y,x });
			}
		}
	}

	if (num > 0)
	{
		auto columnIndex = AnalizeVector(playerPositions, player, [&](Position p, size_t idx) { return area[idx][p.x]; }).x;
		auto rowIndex = AnalizeVector(playerPositions, player, [&](Position p, size_t idx) { return area[p.y][idx]; }).y;
		
		vector<int32_t> indexes;
		if (columnIndex == -1 && rowIndex == -1)
		{
			const size_t index = input::GetRandomNum(0, num - 1);
			return positions[index];
		}
		else if (columnIndex >= 0)
		{
			for (size_t y = 0; y < _data->Size(); y++)
			{
				if (area[y][columnIndex] != player->Chip)
					indexes.push_back(y);
			}
			return { indexes.at(input::GetRandomNum(0, indexes.size() - 1)), columnIndex };
		}
		else if (rowIndex >= 0)
		{
			for (size_t x = 0; x < _data->Size(); x++)
			{
				if (area[rowIndex][x] != player->Chip)
					indexes.push_back(x);
			}
			return { rowIndex, indexes.at(input::GetRandomNum(0, indexes.size() - 1))};
		}
	}

	return {0, 0};
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
			{
				next.x += sign;
				if (next.x == _data->Size())
					return current;
			}
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
			{
				next.y += sign;
				if (next.y == _data->Size())
					return current;
			}
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
