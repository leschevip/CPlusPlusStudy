#include "Engine.h"

void Engine::InitComponents()
{
	if (_perspective == nullptr)
		throw;

	_data = new GameData(_perspective);
	_render = new Render(_perspective, _data);
}

Engine::Engine() : _data(0), _render(0), _perspective(0)
{
}

Engine::~Engine()
{
	delete _render;
	delete _data;
	delete _perspective;
}

void Engine::SetPerspective(Perspective * const p)
{
	_perspective = p;
}

int Engine::ProccessInputKey(const int32_t& key)
{
	if (_data->IsEndGame())
		return 1;

	MVector moveVector;
	double angle(0.0f);
	switch (key)
	{
	case KEY_LEFT:
		moveVector.x = -1;
		break;
	case KEY_RIGHT:
		moveVector.x = 1;
		break;
	case KEY_DOWN:
		moveVector.y = 1;
		break;
	case 32:
		angle = M_PI_2;
		break;
	default:
		break;
	}
 	TrySetNextPosition(moveVector, angle);
	_render->Rendering();
	return 0;
}

// pos - ����� ������� ������ ������ � ������� ��������� ������� �������.
// angle - ���� �������� ������
void Engine::TrySetNextPosition(const MVector& vect, const double& angle)
{
  	auto figure = _data->GameFigure();
	auto gameAreaBounds = _perspective->Game->ClientPart();
	auto pos = *figure->PosCS() + vect;
	auto posData = _data->GetFigurePos(pos, angle);

	// ��������� ����������� �� ��� � ������� �������
	const Point newLeftTop = posData.NewBounds.LeftTop();
	const Point newRightBottom = posData.NewBounds.RightBottom();
	// ����������� ������ ������� � ������ �� ������� ������� ������� �������
	auto fgIsOutOfSide = !gameAreaBounds.XIn(newRightBottom.x) || !gameAreaBounds.XIn(newLeftTop.x);
	// ����������� ������ ������� � ������ �� ������ ������� ������� �������
	auto fgIsOutOfBottom = !gameAreaBounds.YIn(newRightBottom.y) && gameAreaBounds.YIn(newLeftTop.y);
	// ������ ������������ � �������� �������� ������� �������
	auto fgIsIntersect = posData.IsIntersect;

	// ���� ��� ����������� ����� ������ �� ������� �� ����� ��� ������ ������� ��� ������������ � ������ ������� �� �������
	// ���� ��� �������� �� ������� �� ��� ������� ������� ������ ��� ������������ � ������ ������� �� �������
	if ((vect.x != 0 && !fgIsOutOfBottom && (fgIsOutOfSide || fgIsIntersect)) || 
		(vect.y == 0 && angle != 0 && (fgIsOutOfBottom || fgIsIntersect || fgIsOutOfSide)))
	{ 
		return;
	}

	// ���� �������� ����� ������ ������� ������ ��� ����������� � ����� ��������, �� ������� ���� � ���������� ����� ������
	if (vect.y != 0 && (fgIsOutOfBottom || fgIsIntersect))
	{
		_data->CheckScoreAndGetNext();
	}
	// ������� ������
	else
	{
 		_data->SetFigurePos(posData);
	}
}

bool Engine::IsEndGame()
{
	return _data->IsEndGame();
}


int Engine::TickTack()
{
	bool isEnd = _data->IsEndGame();
	if (!isEnd)
	{
		TrySetNextPosition(MVector(0, 1), 0);
	}
	_render->Rendering();
	return isEnd;
}
