#include "GameData.h"

GameData::GameData(Perspective* p) : _totalScore(0), _p(p)
{
	_figures.push_back(FigureCreator::Create(FigureType::F1));
	_figures.push_back(FigureCreator::Create(FigureType::F2));
	_figures.push_back(FigureCreator::Create(FigureType::F3));
	Init();
	GameFigureActive = CreateRandomFigure(_p->Game);
	PreviewFigureActive = CreateRandomFigure(_p->Preview);
};



void GameData::Init()
{
	int H = _p->MaxCharHeightCount();
	int W = _p->MaxCharWidthCount();
	for (size_t r = 0; r < H; r++)
	{
		_busyPoints.insert({ r, new bool[W] {false} });
	}
}

FigureInstance* GameData::CreateRandomFigure(OutputArea* const output)
{
	int index = GetRandomNumber(0, _figures.size()-1);
	auto f = _figures.at(index);
	return CreateFigure(f, output);
}

FigureInstance* GameData::CreateFigure(Figure* const model, OutputArea* const  output)
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


vector<Point> GameData::GetPos(FigureInstance* const fg)
{
	return GetPos(fg, *fg->PosCS(), fg->Angle());
}

vector<Point> GameData::GetPos(FigureInstance* fg, const Point& pos, const double& angle)
{
	vector<Point> newPoints;
	// повернуть фигуру в ЛСК и сдвинуть ЛСК на предлагаемую позицию
	for (auto point : *fg->Model()->Points())
	{
		const int xx = round(point.x * cos(angle) - point.y * sin(angle)) + pos.x;
		const int yy = round(point.x * sin(angle) + point.y * cos(angle)) + pos.y;
		newPoints.push_back(Point(xx, yy));
	}
	return newPoints;
}

FigurePositionData GameData::GetFigurePos(FigureInstance* const fg)
{
	FigurePositionData data;
	data.Angle = fg->Angle();
	data.pos = *fg->PosCS();
	data.NewPoints = GetPos(fg);
	data.NewBounds = GetVectorPointsBounds(data.NewPoints);
	data.IsIntersect = false;
	return data;
}

FigurePositionData GameData::GetFigurePos(const Point& p, const double& angle)
{
	auto fg = GameFigureActive; 
	FigurePositionData data;
	double curAngle = (fg->Angle() + angle) == 2 * M_PI ? 0 : fg->Angle() + angle;
	data.Angle = curAngle;
	data.pos = p;
	data.NewPoints = GetPos(fg, p, curAngle);
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
	{
		if (!_busyPoints.contains(point.y))
			_busyPoints.insert({ point.y, new bool[_p->MaxCharWidthCount()] });
		bool *ptr = _busyPoints.at(point.y);
		ptr[point.x] = true;
	}

	auto fgBounds = GameFigureActive->Bounds();
	auto rect = _p->Game->ClientPart();
	auto width = rect.Width();
	for (size_t r = fgBounds.Top(); r <= fgBounds.Bottom(); r++)
	{
		bool isBusy(true);
		for (size_t c = rect.Left(); c < rect.Right(); c++)
		{
			if (!IsBusy(r, c))
			{
				isBusy = !isBusy;
				break;
			}
		}
		if (isBusy)
		{
			bool* row = _busyPoints.at(r);
			for (size_t ri = r - 1; ri >= 0; ri--)
				_busyPoints[r] = _busyPoints[r - 1];
			_busyPoints[0] = new bool[_p->MaxCharWidthCount()]{ false };

			_totalScore += width;
			delete[] row;
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

bool GameData::IsBusy(const int& r, const int& c)
{
	return _busyPoints.at(r)[c];
}

int GameData::TotalScore()
{
	return _totalScore;
}

bool GameData::IsEndGame()
{
	auto rect = _p->Game->ClientPart();
	for (size_t c = rect.Left(); c < rect.Right(); c++)
	{
		bool* busyRowCells = _busyPoints.at(rect.Top());
		if (busyRowCells[c])
			return true;
	}
	return false;
}


GameData::~GameData()
{
	if (GameFigureActive != nullptr)
		delete GameFigureActive;
	if (PreviewFigureActive != nullptr)
		delete PreviewFigureActive;

	for (auto* f : _figures)
		delete f;
	_figures.clear();

	for (auto item : _busyPoints)
		delete[] item.second;
	_busyPoints.clear();
	
	_p = nullptr;
}
