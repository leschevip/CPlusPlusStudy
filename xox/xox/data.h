#pragma once
#include <string>

#define OUT

enum class Progress
{
	IN_PROGRESS,
	DRAW,
	HUMAN_WON,
	AI_WON
};

struct Position
{
	int32_t y{ 0 };
	int32_t x{ 0 };
};

struct Player
{
	std::string Name;
	char Chip;
	bool IsAI;
};

struct State
{
	Progress ProgressGame;
	Player* Winner;

	~State()
	{
		Winner = nullptr;
	}
};

struct AiInfo
{ 
	Position pos; 
	int32_t count; 
};

class Data
{
private:
	vector<Player*> _players;
	size_t _activePlayer;
	size_t _size;
	size_t _playersCount;
	char** _area;
	State _progressState;
	Position _currentPosition;
	
	void ResetCurrentPosition()
	{
		for (size_t y = 0; y < _size; y++)
		{
			for (size_t x = 0; x < _size; x++)
			{
				if (_area[y][x] == EMPTYCHAR)
				{
					_currentPosition.x = x;
					_currentPosition.y = y;
					return;
				}
			}
		}
	}

public:

	Data() : _area(nullptr), _activePlayer(0), _size(0), _playersCount(0), _progressState({ Progress::IN_PROGRESS , nullptr})
	{
	}

	const char EMPTYCHAR = '_';

	inline char** Area() { return _area; }
	
	inline size_t Size() { return _size; }

	inline size_t PlayersQuantity() { return _playersCount; }
	
	inline Player* ActivePlayer() { return _players.at(_activePlayer); };

	inline bool IsProgress() { return _progressState.ProgressGame == Progress::IN_PROGRESS; };
	
	inline vector<Player*>* Players() { return &_players; };
	
	inline void SetActivePlayer(size_t index) { _activePlayer = index; }
	
	inline void SetPlayersQuantity(size_t count) { _playersCount = count; }

	void SetProgressState(State state)
	{ 
		_progressState = state;
	}

	inline Player* Winner() { return _progressState.Winner; }

	inline State State() { return _progressState; }

	inline Position CurrentPosition() { return _currentPosition; }

	inline void SetCurrentPosition(Position pos) { _currentPosition = pos; }

	void AppyUserChoice(Position position) 
	{ 
		_area[position.y][position.x] = ActivePlayer()->Chip;
		if (_players.size() - 1 > _activePlayer)
		{
			_activePlayer++;
		}
		else
		{
			_activePlayer = 0;
		}
		ResetCurrentPosition();
	}

	void SetAreaSize(size_t size)
	{ 
		_size = size; 
		_area = new char* [_size];
		for (size_t i = 0; i < _size; i++)
		{
			_area[i] = new char[_size];
			for (size_t k = 0; k < _size; k++)
				_area[i][k] = EMPTYCHAR;
		}
	}

	~Data()
	{
		for (auto* p : _players)
			delete p;
		
		_players.clear();

		for (size_t y = 0; y < _size; y++)
			delete[] _area[y];
		delete[] _area;
	}
};