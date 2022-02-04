#include <Windows.h>
#include "Engine.h"

using namespace std;


int main()
{
	Engine::MainLoop(100, 100, 1024, 768);
	return 0;
}