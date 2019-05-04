#include "D2DWindow.h"
#include "Resource.h"
#include <thread>


LRESULT __stdcall D2DHelper::DefaultWindowProcess(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(h, msg, wp, lp);
	}
	return 0;
}

D2DHelper::D2DWindow::D2DWindow(HINSTANCE hinst)
{
	customwcex = WNDCLASSEXW();
	customwcex.cbSize = 0;
	defwcex = WNDCLASSEXW();
	Instance = hinst;
	{
		ID2D1Factory* f = nullptr;
		if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &f) == S_OK)
			Factory.reset(f);
		else
			PostQuitMessage(20);
	}
	if (defwcex.cbSize != sizeof(WNDCLASSEXW))
	{
		defwcex.hInstance = hinst;
		RegisterClassExW(&defwcex);
	}
}

D2DHelper::D2DWindow::D2DWindow(HINSTANCE hinst,WNDCLASSEXW wcex)
{
	Instance = hinst;
	{
		ID2D1Factory* f = nullptr;
		if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &f) == S_OK)
			Factory.reset(f);
		else
			PostQuitMessage(20);
	}
	customwcex = wcex;
	RegisterClassExW(&wcex);
}

void D2DHelper::D2DWindow::StartRenderProcess(int nCmdShow)
{
	auto winhandle = CreateWindowExW(0, customwcex.cbSize == sizeof(WNDCLASSEXW)?customwcex.lpszClassName:L"D2DHelper::D2DWindow::DefaultD2DWindowClassEX",
		L"MainD2DWindow",
		WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		1200, 750, 200, 150, 0, 0, this->Instance, 0);//res 1440x900
	ShowWindow(winhandle, nCmdShow);
	UpdateWindow(winhandle);
	MSG msg;
	while (GetMessageW(&msg, winhandle, 0, 0))
	{
		if (!TranslateAcceleratorW(winhandle, LoadAcceleratorsW(Instance, MAKEINTRESOURCEW(IDC_MAINWINDOW)), &msg))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
}


D2DHelper::D2DWindow::~D2DWindow()
{

}


void D2DHelper::Deleters::FactoryDeleter::operator() (ID2D1Factory* target)
{
	target->Release();
}