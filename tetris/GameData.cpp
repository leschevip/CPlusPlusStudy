#include "GameData.h"

GameData::GameData(Perspective* p) : _totalScore(0), _p(p)
{
	_figures.push_back(FigureCreator::Create(FigureType::F1));
	_figures.push_back(FigureCreator::Create(FigureType::F2));
	Init();
	GameFigureActive = CreateRandomFigure(_p->Game);
	PreviewFigureActive = CreateRandomFigure(_p->Preview);
};



void GameData::Init()
{
	int H = _p->MaxCharHeightCount();
	int W = _p->MaxCharWidthCount();
	_busyPoints = new bool* [H];
	for (int r = 0; r < H; r++)
	{
		_busyPoints[r] = new bool[W];
		for (int c = 0; c < W; c++)
			_busyPoints[r][c] = false;
	}
}

FigureInstance* GameData::CreateRandomFigure(OutputArea* output)
{
	int index = GetRandomNumber(0, _figures.size()-1);
	auto f = _figures.at(index);
	return CreateFigure(f, output);
}

FigureInstance* GameData::CreateFigure(Figure* model, OutputArea* output)
{
	auto area = output->ClientPart();
	Point* dp = nullptr;
	if (output->IsType(AreaType::GAME))
	{
		dp = new Point(area.Width() / 2, 0);
	}
	else if (output->IsType(AreaType::PREVIEW))
	{
		dp = new Point(area.Width() / 2 + area.Left(), area.Height() / 2 + area.Top());
	}
	auto* fg = new FigureInstance(model, dp);
	fg->SetData(GetFigurePos(fg));
	return fg;
}


FigureInstance* GameData::GameFigure()
{
	return GameFigureActive;
}

FigureInstance* GameData::PreviewFigure()
{
	return PreviewFigureActive;
}

vector<Point> GameData::GetPos(FigureInstance* fg)
{
	return GetPos(fg, *fg->PosCS(), fg->Angle());
}

vector<Point> GameData::GetPos(FigureInstance* fg, const Point& pos, const double angle)
{
	double angl = fg->Angle() + angle;
	vector<Point> newPoints;
	// повернуть фигуру в ЛСК и сдвинуть ЛСК на предлагаемую позицию
	for (auto point : *fg->Model()->Points())
	{
		const int xx = point.x * cos(angl) - point.y * sin(angl) + pos.x;
		const int yy = point.x * sin(angl) + point.y * cos(angl) + pos.y;
		newPoints.push_back(Point(xx, yy));
	}
	return newPoints;
}

FigurePositionData GameData::GetFigurePos(FigureInstance* fg)
{
	FigurePositionData data;
	data.Angle = fg->Angle();
	data.pos = *fg->PosCS();
	data.NewPoints = GetPos(fg);
	data.NewBounds = GetVectorPointsBounds(data.NewPoints);
	data.IsIntersect = false;
	return data;
}

FigurePositionData GameData::GetFigurePos(const Point& p, const double angle)
{
	auto fg = GameFigureActive; 
	FigurePositionData data;
	data.Angle = fg->Angle() + angle;
	data.pos = p;
	data.NewPoints = GetPos(fg, p, angle);
	data.NewBounds = GetVectorPointsBounds(data.NewPoints);
	data.IsIntersect = false;
	for (auto point : data.NewPoints)
	{
		if (point.x > 0 && point.y > 0 && _busyPoints[point.y][point.x])
		{
			data.IsIntersect = _busyPoints[point.y][point.x];
			if (data.IsIntersect)
				break;
		}
	}
	return data;
}

void GameData::SetFigurePos(const FigurePositionData& data)
{
	GameFigureActive->SetData(data);
}

void GameData::CheckScoreAndGetNext()
{
	for (auto point : *GameFigureActive->Points())
		_busyPoints[point.y][point.x] = true;

	auto fgBounds = GameFigureActive->Bounds();
	auto width = _p->MaxCharWidthCount();
	for (int r = fgBounds.Top(); r <= fgBounds.Bottom(); r++)
	{
		bool isBusy(false);
		for (int c = 0; c < width; c++)
		{
			isBusy = _busyPoints[r][c];
			if (!isBusy)
				break;
		}
		if (isBusy)
		{
			for (int c = 0; c < width; c++)
				_busyPoints[r][c] = !_busyPoints[r][c];

			_totalScore += width;
		}
	}

	FigureInstance* tmp(nullptr);
	tmp = GameFigureActive;
	GameFigureActive = CreateFigure(PreviewFigureActive->Model(), _p->Game);
	delete tmp;

	tmp = PreviewFigureActive;
	PreviewFigureActive = CreateRandomFigure(_p->Preview);
	delete tmp;
}

bool GameData::IsBusy(const int r, const int c)
{
	return _busyPoints[r][c];
}

int GameData::TotalScore()
{
	return _totalScore;
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

	int H = _p->MaxCharHeightCount();
	for (int i = 0; i < H; i++)
	{
		delete[] _busyPoints[i];
	}
	delete[] _busyPoints;
	_busyPoints = nullptr;
	_p = nullptr;
}
