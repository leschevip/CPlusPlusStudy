#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <map>
#include <math.h>
#include "Figure.h";
#include "FigureCreator.h";
#include "Perspective.h";
#include "common.h";
#include "FigurePositionData.h"

using namespace std;

class GameData
{
private:
	int _totalScore;
	Perspective* _p;
	vector<Figure*> _figures;
	map<int, bool*> _busyPoints;
	FigureInstance* GameFigureActive;
	FigureInstance* PreviewFigureActive;
	
	void Init();
	FigureInstance* CreateRandomFigure(OutputArea* output);
	FigureInstance* CreateFigure(Figure* model, OutputArea* output);
	vector<Point> GetPos(FigureInstance* fg);
	vector<Point> GetPos(FigureInstance* fg, const Point& pos, const double angle);
	FigurePositionData GetFigurePos(FigureInstance* fg);
public:
	GameData(Perspective* p);
	~GameData();
	void CheckScoreAndGetNext();
	bool IsBusy(const int r, const int c);
	int TotalScore();
	bool IsEndGame();
	FigureInstance* GameFigure();
	FigureInstance* PreviewFigure();
	FigurePositionData GetFigurePos(const Point& p, const double angle);
	void SetFigurePos(const FigurePositionData& data);
};