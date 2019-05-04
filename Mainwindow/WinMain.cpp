#include "framework.h"
#include "D2DWindow.h"
int __stdcall wWinMain(HINSTANCE instance, HINSTANCE previnst, wchar_t* cmdline, int cmdshow)
{
	D2DHelper::D2DWindow MainWindow(instance);
	MainWindow.StartRenderProcess(cmdshow);
	return 0;
}