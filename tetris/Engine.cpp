#include "Engine.h"

// HHOOK hook;
Engine en;
HANDLE hTimer = NULL;
bool isGameEnd;
/*
LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{
		if (wParam == WM_KEYDOWN)
		{
 			auto kbStruct = *((KBDLLHOOKSTRUCT*)lParam);
  			en.ProccessInputKey(kbStruct.vkCode);
		}
	}

	return CallNextHookEx(hook, nCode, wParam, lParam);
}
*/

CRectangle GetConsoleViewPort(HWND hwnd, int x, int y, int w, int h)
{
	MoveWindow(hwnd, x, y, w, h, TRUE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return CRectangle(info.srWindow.Left, info.srWindow.Top, info.srWindow.Right, info.srWindow.Bottom);
}

unsigned long _stdcall MainTimer(void*)
{
	int nCount = 0;
	while (true)
	{
		WaitForSingleObject(hTimer, 1000);
		isGameEnd = en.TickTack();
		if (isGameEnd)
			return 0;
	}
	return 0;
}


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

void Engine::SetPerspective(Perspective* p)
{
	_perspective = p;
}

int Engine::ProccessInputKey(int key)
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
void Engine::TrySetNextPosition(const MVector& vect, const double angle)
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
	// else
	//{
	//	_render->RenderingEndGame();
	//}
	return isEnd;
}

void Engine::MainLoop(int x, int y, int w, int h)
{
	HWND hwnd = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(hwnd, 1);

	en.SetPerspective(new Perspective(GetConsoleViewPort(hwnd, 100, 100, 1024, 768)));
	en.InitComponents();
	

	DWORD tid;
	hTimer = CreateEvent(NULL, FALSE, FALSE, NULL);
	CreateThread(NULL, 0, MainTimer, NULL, 0, &tid);
	SetEvent(hTimer);

	MSG message;
	while (true)
	{
		if (isGameEnd)
		{
			int key = getch();
			if (key == 27)
				break;
		}
		else
		{
			isGameEnd = en.ProccessInputKey(getch());
		}
	}
	CloseHandle(hTimer);
	hTimer = NULL;
}
