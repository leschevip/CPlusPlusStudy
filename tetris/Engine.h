#pragma once
#include "Perspective.h"
#include "GameData.h"
#include "Render.h"

using namespace std;

class Engine
{
private:
	Perspective* _perspective;
	GameData* _data;
	Render* _render;
public:

	Engine();
	int TickTack();
	void SetPerspective(Perspective* const p);
	void InitComponents();	
	int ProccessInputKey(const int32_t& key);
	void TrySetNextPosition(const MVector& vect, const double& angle);
	bool IsEndGame();
	~Engine();

};