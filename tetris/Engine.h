#pragma once
#define _USE_MATH_DEFINES

#include <Windows.h>
#include "Perspective.h"
#include "GameData.h"
#include "Render.h"
#include "Timer.h"
#include <math.h>
//#include <conio.h>

using namespace std;

class Engine
{
private:
	Perspective* _perspective;
	GameData* _data;
	Render* _render;
public:

	static void MainLoop(int x, int y, int w, int h);
	Engine();
	int TickTack();
	void SetPerspective(Perspective* p);
	void InitComponents();	
	int ProccessInputKey(int key);
	void TrySetNextPosition(const MVector& vect, const double angle);
	bool IsEndGame();
	~Engine();

};