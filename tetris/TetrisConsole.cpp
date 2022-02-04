
#include <iostream>
#include "Perspective.h"
#include "Render.h";
#include "GameData.h";
#include "FigureCreator.h"
#include "Engine.h"

using namespace std;

HHOOK hook;

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        if (wParam == WM_KEYDOWN)
        {
            auto kbStruct = *((KBDLLHOOKSTRUCT*)lParam);
            kbStruct.vkCode;
        }
    }
    return CallNextHookEx(hook, nCode, wParam, lParam);
}

int main()
{
    auto hwnd = FindWindowA("ConsoleWindowClass", "ConsoleApplication2");
    ShowWindow(hwnd, 1);
    if (!(hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0)))
    {
        MessageBoxA(NULL, "Something wrong!", "Error", MB_ICONERROR);
    }

    MSG message;
    while (true)
    {
        GetMessage(&message, NULL, 0, 0);
    }

    /*
    Engine en(100, 100, 1024, 768);
    en.MainLoop();
    */
    /*
    auto figure = FigureCreator::Create(FigureType::F1);
    string str = "";
    for (int i = 0; i < figure->PointsCount; i++)
    {
        float x = *(figure->Points + 2 * i);
        float y = *(figure->Points + 2 * i + 1);

        int wcount = x / p.CharW();
        int hcount = y / p.CharH();
        int ii = 1;
        
    }
    */

}