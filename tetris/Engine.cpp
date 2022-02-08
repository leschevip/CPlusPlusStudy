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

// pos - новая позиция центра фигуры в системе координат игровой области.
// angle - угол поворота фигуры
void Engine::TrySetNextPosition(const MVector& vect, const double& angle)
{
  	auto figure = _data->GameFigure();
	auto gameAreaBounds = _perspective->Game->ClientPart();
	auto pos = *figure->PosCS() + vect;
	auto posData = _data->GetFigurePos(pos, angle);

	// проверяем вписывается ли она в игровую область
	const Point newLeftTop = posData.NewBounds.LeftTop();
	const Point newRightBottom = posData.NewBounds.RightBottom();
	// перемещение фигуры привело к выходу за боковые границы игровой области
	auto fgIsOutOfSide = !gameAreaBounds.XIn(newRightBottom.x) || !gameAreaBounds.XIn(newLeftTop.x);
	// перемещение фигуры привело к выходу за нижнюю границу игровой области
	auto fgIsOutOfBottom = !gameAreaBounds.YIn(newRightBottom.y) && gameAreaBounds.YIn(newLeftTop.y);
	// фигура пересекается с занятыми ячейками игровой области
	auto fgIsIntersect = posData.IsIntersect;

	// если при перемещении влево вправо мы выходим за левую или правую границы или пересекаемся с другой фигурой то выходим
	// если при повороте мы выходим за все границы области вывода или пересекаемся с другой фигурой то выходим
	if ((vect.x != 0 && !fgIsOutOfBottom && (fgIsOutOfSide || fgIsIntersect)) || 
		(vect.y == 0 && angle != 0 && (fgIsOutOfBottom || fgIsIntersect || fgIsOutOfSide)))
	{ 
		return;
	}

	// если достигли конца нижней области вывода или пересечения с иными фигурами, то считаем очки и генерируем новую фигуру
	if (vect.y != 0 && (fgIsOutOfBottom || fgIsIntersect))
	{
		_data->CheckScoreAndGetNext();
	}
	// двигаем фигуру
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
