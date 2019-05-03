#include "D2DWindow.h"



BOOL D2DHelper::D2DWindow::WindowProcess(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(h, msg, wp, lp);
	}
	return TRUE;
}

D2DHelper::D2DWindow::D2DWindow(HINSTANCE hinst)
{
	Instance = hinst;
	{
		ID2D1Factory* f = nullptr;
		if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &f) == S_OK)
			Factory.reset(f);
		else
			PostQuitMessage(20);
	}
}

void D2DHelper::D2DWindow::Render()
{
}


D2DHelper::D2DWindow::~D2DWindow()
{
}


void D2DHelper::Deleters::FactoryDeleter::operator() (ID2D1Factory* target)
{
	target->Release();
}