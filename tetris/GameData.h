#pragma once
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
	Perspective* _p;
	vector<Figure*> _figures;
	bool** _busyPoints;
	FigureInstance* volatile GameFigureActive;
	FigureInstance* volatile PreviewFigureActive;
	
	int _totalScore;
	void Init();
	FigureInstance* CreateRandomFigure(OutputArea* output);
	FigureInstance* CreateFigure(Figure* model, OutputArea* output);


	vector<Point> GetPos(FigureInstance* fg);
	vector<Point> GetPos(FigureInstance* fg, const Point& pos, const double angle);
public:
	
	static const int C_INITIAL_SPEED = 1;
	static const int C_PREVIEW_INITIAL_SPEED = 0;
	static const int C_INITIAL_ANGLE = 0;

	//std::ofstream _log;

	GameData(Perspective* p);
	~GameData();
	FigureInstance* GameFigure();
	FigureInstance* PreviewFigure();

	FigurePositionData GetFigurePos(const Point& p,  const double angle);
	FigurePositionData GetFigurePos(FigureInstance* fg);
	void SetFigurePos(const FigurePositionData& data);
	void CheckScoreAndGetNext();
	bool IsBusy(const int r, const int c);
	int TotalScore();
};