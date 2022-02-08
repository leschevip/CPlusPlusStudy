#include "Render.h"

Render::Render( Perspective* const p, GameData* const data) : _data(data), _p(p), _frame(nullptr)
{
	initFrame();
	initscr();
	keypad(stdscr, true);
	
	auto win = stdscr;
	win->_sync = true;
}

int Render::Rendering()
{
	clear();

	auto gameArea = _p->Game->ClientPart();
	auto previewArea = _p->Preview->ClientPart();
	auto scoreArea = _p->Score->ClientPart();
	clearFrame(gameArea);
	clearFrame(previewArea);
	clearFrame(scoreArea);

	auto result = _data->IsEndGame();
	
	for (int r = gameArea.Top(); r <= gameArea.Bottom(); r++)
		for (int c = gameArea.Left(); c <= gameArea.Right(); c++)
			if (_data->IsBusy(r, c))
				_frame[r][c] = C_BOUNDS_CHAR;

	for (auto point : *_data->GameFigure()->Points())
	{
		if (gameArea.PointIn(point))
			_frame[point.y][point.x] = C_BOUNDS_CHAR;
	}

	for (auto point : *_data->PreviewFigure()->Points())
	{
		if (previewArea.PointIn(point))
			_frame[point.y][point.x] = C_BOUNDS_CHAR;
	}

	int r = scoreArea.Top() + scoreArea.Height() / 2;
	int c = scoreArea.Left() + 1;

	string s = " Score: " + to_string(_data->TotalScore()) + " points" + (result ? " GAME OWER!!!" : "");
	const char* chrs = s.c_str();
	int i = 0;
	char chr = chrs[i];
	while (chr != '\0')
	{
		_frame[r][c + i] = chr;
		i++;
		chr = chrs[i];
	}

	auto H = _p->MaxCharHeightCount();
	for (int r = 0; r < H; r++)
		addstr(_frame[r]);

	refresh();

	return result;
}

Render::~Render()
{
	endwin();

	int H = _p->MaxCharHeightCount();
	for (int r = 0; r < H; r++)
		delete[] _frame[r];
	delete[] _frame;

	_data = nullptr;
	_p = nullptr;
	_frame = nullptr;
}

void Render::initFrame()
{
	int H = _p->MaxCharHeightCount();
	int W = _p->MaxCharWidthCount();

	_frame = new char* [H];
	for (int r = 0; r < H; r++)
	{
		_frame[r] = new char[W+1];
		for (int c = 0; c < W; c++)
			_frame[r][c] = C_EMPTY_CHAR;
		_frame[r][W] = '\0';
	}

	auto areaScore = _p->Output(AreaType::SCORE);
	initFrameStatic(areaScore->Bounds());
	auto areaGame = _p->Output(AreaType::GAME);
	initFrameStatic(areaGame->Bounds());
	auto areaPrev = _p->Output(AreaType::PREVIEW);
	initFrameStatic(areaPrev->Bounds());
}

void Render::initFrameStatic(CRectangle& rect)
{
	for (int c = rect.Left(); c <= rect.Right(); c++)
	{
		_frame[rect.Top()][c] = C_BOUNDS_CHAR;
		_frame[rect.Bottom()][c] = C_BOUNDS_CHAR;
	}

	for (int r = rect.Top(); r <= rect.Bottom(); r++)
	{
		_frame[r][rect.Left()] = C_BOUNDS_CHAR;
		_frame[r][rect.Right()] = C_BOUNDS_CHAR;
	}
}

void Render::clearFrame(CRectangle& rect)
{
	for (int r = rect.Top(); r <= rect.Bottom(); r++)
		for (int c = rect.Left(); c <= rect.Right(); c++)
			_frame[r][c] = C_EMPTY_CHAR;
}
