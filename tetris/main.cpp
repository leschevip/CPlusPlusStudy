#include <Windows.h>
#include "Engine.h"

extern const int32_t E_ESC;

using namespace std;

const uint32_t W_TOP = 100;
const uint32_t W_BOTTOM = 100;
const uint32_t W_WIDTH = 1024;
const uint32_t W_HEIGHT = 768;

Engine en;
HANDLE hTimer = NULL;
bool isGameEnd;
// HHOOK hook;

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

CRectangle GetConsoleViewPort(const HWND& hwnd, const uint32_t& x, const uint32_t& y, const uint32_t& w, const uint32_t& h)
{
	MoveWindow(hwnd, x, y, w, h, TRUE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return CRectangle(info.srWindow.Left, info.srWindow.Top, info.srWindow.Right, info.srWindow.Bottom);
}

void MainLoop(const uint32_t& x, const uint32_t& y, const uint32_t& w, const uint32_t& h)
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
			if (key == E_ESC)
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

int main()
{
	MainLoop(W_TOP, W_BOTTOM, W_WIDTH, W_HEIGHT);
	return 0;
}