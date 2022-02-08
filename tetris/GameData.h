#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <map>
#include <math.h>
#include "Figure.h";
#include "FigureCreator.h";
#include "Perspective.h";
#include "FigurePositionData.h"

#pragma warning (disable 6295)
using namespace std;

class GameData
{
private:
	int _totalScore;
	Perspective* _p;
	vector<Figure*> _figures;
	map<int32_t, bool*> _busyPoints;
	FigureInstance* GameFigureActive;
	FigureInstance* PreviewFigureActive;
	
	void Init();
	FigureInstance* CreateRandomFigure(OutputArea* const output);
	FigureInstance* CreateFigure(Figure* const model, OutputArea* const output);
	vector<Point> GetPos(FigureInstance* const fg);
	vector<Point> GetPos(FigureInstance* const fg, const Point& pos, const double& angle);
	FigurePositionData GetFigurePos(FigureInstance* fg);
public:
	GameData(Perspective* constp);
	~GameData();
	void CheckScoreAndGetNext();
	bool IsBusy(const int& r, const int& c);
	int32_t TotalScore();
	bool IsEndGame();
	FigureInstance* GameFigure();
	FigureInstance* PreviewFigure();
	FigurePositionData GetFigurePos(const Point& p, const double& angle);
	void SetFigurePos(const FigurePositionData& data);
};