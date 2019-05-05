#include "framework.h"
#include <string>
#include "D2DWindow.h"



LRESULT __stdcall ShimejiWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void RegisterShimejiWndClass(HINSTANCE hinst)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = ShimejiWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinst;
	wcex.hIcon = nullptr;
	wcex.hCursor = nullptr;
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wcex.lpszMenuName = L"Shimeji-Win32 Mainwindow";
	wcex.lpszClassName = L"Shimeji-Win32 Mainwindow Class";
	wcex.hIconSm = nullptr;
	if (RegisterClassExW(&wcex) == 0)
	{
		throw std::exception("Register Window Class Failed");
	}
}

int __stdcall wWinMain(HINSTANCE instance, HINSTANCE previnst, wchar_t* cmdline, int cmdshow)
{
	RegisterShimejiWndClass(instance);
	auto mainwindow = CreateWindowExW(WS_EX_LAYERED, L"Shimeji-Win32 Mainwindow Class", L"Test",
		WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CW_USEDEFAULT,
		0, 150, 200, nullptr, nullptr, instance, nullptr);
	
	if (mainwindow == NULL)
		return 20;

	D2DHelper::D2DWindowV2 Window(mainwindow);
	

	ShowWindow(mainwindow, cmdshow);

	MSG msg;
	while (GetMessageW(&msg,nullptr,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return (int) msg.wParam;
}
