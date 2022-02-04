#include "GameData.h"

GameData::GameData(Perspective* p) : ScoreCount(0), _frame(nullptr), _p(p)
{
	_figures.push_back(FigureCreator::Create(FigureType::F1));
	_frame = InitFrame();
	_frameBuffer = InitFrame();
	GameFigureActive = CreateRandomFigure(_p->Game);
	PreviewFigureActive = CreateRandomFigure(_p->Preview);
	//_log.open("E:\\log.txt"); // окрываем файл для записи
	
};

void GameData::ClearFrame(char** frame, CRectangle& rect)
{
	for (int r = rect.Top(); r <= rect.Bottom(); r++)
		for (int c = rect.Left(); c <= rect.Right(); c++)
			frame[r][c] = C_EMPTY_CHAR;
}

char** GameData::InitFrame()
{
	int H = _p->MaxCharHeightCount();
	int W = _p->MaxCharWidthCount();

	char** frame = new char* [H];
	for (int r = 0; r < H; r++)
	{
		frame[r] = new char[W+1];
		for (int c = 0; c < W; c++)
			frame[r][c] = C_EMPTY_CHAR;
		frame[r][W] = '\0';
	}

	auto areaScore = Output(AreaType::SCORE);
	InitStaticFramePart(frame, areaScore->Bounds());
	auto areaGame = Output(AreaType::GAME);
	InitStaticFramePart(frame, areaGame->Bounds());
	auto areaPrev = Output(AreaType::PREVIEW);
	InitStaticFramePart(frame, areaPrev->Bounds());
	return frame;
}

void GameData::InitStaticFramePart(char** frame, CRectangle& rect)
{
	for (int c = rect.Left(); c <= rect.Right(); c++)
	{
		frame[rect.Top()][c] = C_BOUNDS_CHAR;
		frame[rect.Bottom()][c] = C_BOUNDS_CHAR;
	}

	for (int r = rect.Top(); r <= rect.Bottom(); r++)
	{
		frame[r][rect.Left()] = C_BOUNDS_CHAR;
		frame[r][rect.Right()] = C_BOUNDS_CHAR;
	}
}

FigureInstance* GameData::CreateRandomFigure(OutputArea* output)
{
	int index = GetRandomNumber(0, _figures.size()-1);
	
	auto f = _figures.at(index);
	auto v = vector<Point>(f->Points);

	auto area = output->ClientPart();
	
	int x = 0, y = 0;
	if (output->IsType(AreaType::GAME))
	{
		x = area.Width() / 2 + area.Left();
		y = -f->Size.Height() / 2 + area.Top();
	}
	else if (output->IsType(AreaType::PREVIEW))
	{
		x = area.Width() / 2 + area.Left();
		y = area.Height() / 2 + area.Top();
	}
	Point* dp = new Point(x, y);
	auto* fInstance = new FigureInstance(f, v);
	fInstance->Size->MoveBy(dp->x, dp->y);
	fInstance->Position = dp;
	for (Point& point : fInstance->Points)
		point += *dp;

	return fInstance;
}

int GameData::FrameCols()
{
	return _p->MaxCharWidthCount();
}

int GameData::FrameRows()
{
	return _p->MaxCharHeightCount();
}

char** GameData::Frame()
{
	return _frame;
}

void GameData::CalcState()
{
	auto gameArea = _p->Game->ClientPart();
	auto previewArea = _p->Preview->ClientPart();
	ClearFrame(_frame, gameArea);
	ClearFrame(_frame, previewArea);

	for (auto& point : _filledPoints)
	{
		_frame[point.y][point.x] = C_BOUNDS_CHAR;
	}

	for (auto& point : GameFigureActive->Points)
	{
		if (gameArea.In(point))
			_frame[point.y][point.x] = C_BOUNDS_CHAR;
	}

	for (auto& point : PreviewFigureActive->Points)
	{
		if (previewArea.In(point))
			_frame[point.y][point.x] = C_BOUNDS_CHAR;
	}
}

void GameData::Move(MVector& vect, float angle)
{
	auto size = GameFigureActive->Size;
	auto outputGame = _p->Game;
	auto outputPreview = _p->Preview;
	auto area = outputGame->ClientPart();
	
	if ((size->Left() == area.Left() && vect.x < 0) || (size->Right() == area.Right() && vect.x > 0))
	{
		vect.x = 0;
		return;
	}
	else
	{
		//next position
		auto curPoints = GameFigureActive->Points;
		vector<Point> vTmp(curPoints);
		if (angle > 0)
		{
      		int i = 1;
		}

		auto pos = GameFigureActive->Position;
		for (Point& point : vTmp)
		{
			point += vect;

			/*
			if (angle > 0)
			{
				point.x = (point.x - pos->x) * cosf(angle) + (point.y - pos->y) * sin(angle) + pos->x;
				point.y = -(point.x - pos->x) * sinf(angle) + (point.y - pos->y) * cos(angle) + pos->y;
			}
			else
			{
				point += vect;
			}
			*/
		}
			

		bool isIntersect = IsIntersectVectors(vTmp, _filledPoints);
		if (vect.x != 0 && isIntersect)
		{
			return;
		}
		
		if (size->Bottom() != area.Bottom() && !isIntersect)
		{
			GameFigureActive->Points.assign(vTmp.begin(), vTmp.end());
			GameFigureActive->Size->MoveBy(vect.x, vect.y);
			GameFigureActive->Position->x += vect.x;
			GameFigureActive->Position->y += vect.y;
		}
		else 
		{
			_filledPoints.insert(_filledPoints.end(), curPoints.begin(), curPoints.end());
			FigureInstance* tmp(nullptr);

			tmp = GameFigureActive;
			GameFigureActive = CreateRandomFigure(outputGame);
			delete tmp;
			tmp = PreviewFigureActive;
			PreviewFigureActive = CreateRandomFigure(outputPreview);
			delete tmp;
		}
	}
	/*
	if (_log.is_open())
	{
		auto* rect = GameFigureActive->Size;
		_log << "Bottom:" << rect->Bottom() << std::endl;
	}
	*/

	CalcState();
}

GameData::~GameData()
{
	if (GameFigureActive != nullptr)
		delete GameFigureActive;
	if (PreviewFigureActive != nullptr)
		delete GameFigureActive;

	for (auto* f : _figures)
		delete f;
	_figures.clear();

	int H = FrameCols();
	for (int i = 0; i < H; i++)
	{
		delete[] _frame[i];
		delete[] _frameBuffer[i];
	}
	delete[] _frame;
	delete[] _frameBuffer;

	_p = nullptr;
}

OutputArea* GameData::Output(AreaType type)
{
	switch (type)
	{
	case AreaType::EMPTY:
		return nullptr;
	case AreaType::SCORE:
		return _p->Score;
	case AreaType::GAME:
		return _p->Game;
	case AreaType::PREVIEW:
		return _p->Preview;
	case AreaType::SCREEN:
		return _p->Full;
	default:
		break;
	}
	return nullptr;
}
