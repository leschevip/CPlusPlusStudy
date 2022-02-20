
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

typedef int (WINAPI* funPointer)();

int Exec(const HINSTANCE dll, const string& func)
{
    funPointer fun = (funPointer)GetProcAddress(dll, func.c_str());
    return (int)(*fun)();
}

int main()
{
    HINSTANCE dll = LoadLibrary(L"homework.dll");
    if (dll == NULL) return 1;
    
    Exec(dll, "Task1and5");
    Exec(dll, "Task2");
    Exec(dll, "Task3");
    Exec(dll, "Task4");
  
    FreeLibrary(dll);
    return 0;
}