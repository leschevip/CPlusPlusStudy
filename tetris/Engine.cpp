#include "Engine.h"

// HHOOK hook;
Engine en;
HANDLE hTimer = NULL;

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
		en.TickTack();
	}
	return 0;
}


void Engine::InitComponents()
{
	if (_perspective == nullptr)
		throw;

	_data = new GameData(_perspective);
	_render = new Render(_data);
	_mainTimerId = 1;
}

Engine::Engine() : _data(0), _render(0), _perspective(0), _mainTimerId(0)
{
}

void Engine::SetPerspective(Perspective* p)
{
	_perspective = p;
}

void Engine::ProccessInputKey(int key)
{
	MVector moveVector;
	float angle(0.0f);
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
	_data->Move(moveVector, angle);
	_render->Rendering();
}

int Engine::TickTack()
{
	MVector moveVector(0, 1);
	_data->Move(moveVector, 0);
	_render->Rendering();
	return 0;
}

void Engine::MainLoop(int x, int y, int w, int h)
{
	HWND hwnd = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(hwnd, 1);

	/*
	if (!(hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0)))
	{
		MessageBoxA(NULL, "Something wrong!", "Error", MB_ICONERROR);
	}
	*/
	en.SetPerspective(new Perspective(GetConsoleViewPort(hwnd, 100, 100, 1024, 768)));
	en.InitComponents();
	

	DWORD tid;
	hTimer = CreateEvent(NULL, FALSE, FALSE, NULL);
	CreateThread(NULL, 0, MainTimer, NULL, 0, &tid);
	SetEvent(hTimer);

	MSG message;
	while (true)
	{
		en.ProccessInputKey(getch());
	}

	CloseHandle(hTimer);
}
