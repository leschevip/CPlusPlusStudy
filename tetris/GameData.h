#pragma once
#include <vector>
#include <math.h>
#include "Figure.h";
#include "FigureCreator.h";
#include "Perspective.h";
#include "common.h";

using namespace std;

class GameData
{
private:
	Perspective* _p;
	char** _frameBuffer;
	char** _frame;
	vector<Figure*> _figures;
	vector<Point> _filledPoints;
	FigureInstance* GameFigureActive;
	FigureInstance* PreviewFigureActive;
	int ScoreCount;

	void ClearFrame(char** frame, CRectangle& rect);
	char** InitFrame();
	void InitStaticFramePart(char** frame, CRectangle& rect);
	void CalcState();
	FigureInstance* CreateRandomFigure(OutputArea* output);
public:
	static const const char C_EMPTY_CHAR = ' ';
	static const const char C_BOUNDS_CHAR = '#';
	static const int C_INITIAL_SPEED = 1;
	static const int C_PREVIEW_INITIAL_SPEED = 0;
	static const int C_INITIAL_ANGLE = 0;

	//std::ofstream _log;

	GameData(Perspective* p);
	~GameData();
	OutputArea* Output(AreaType type);
	void Move(MVector& vect, float angle);
	char** Frame();
	int FrameCols();
	int FrameRows();

	

};