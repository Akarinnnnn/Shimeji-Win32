#include "framework.h"
#include "D2DWindow.h"
int __stdcall wWinMain(HINSTANCE instance, HINSTANCE previnst, wchar_t* cmdline, int cmdshow)
{
	MSG msg;
	D2DHelper::D2DWindow MainWindow(instance);
	MainWindow.StartRenderProcess(cmdshow);
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}