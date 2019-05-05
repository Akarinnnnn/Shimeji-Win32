#include "D2DWindow.h"
#include "Resource.h"
#include <thread>
using namespace std;

LRESULT __stdcall D2DHelper::DefaultWindowProcess(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_PAINT:
		
		break;
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
	if (defwcex.cbSize != sizeof(WNDCLASSEXW))
	{
		defwcex.hInstance = hinst;
		RegisterClassExW(&defwcex);
	}
	this->wndhandle = CreateWindowExW(0, L"D2DHelper::D2DWindow::DefaultD2DWindowClassEX",
		L"MainD2DWindow",
		WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		1200, 750, 200, 150, 0, 0, this->Instance, 0);//res 1440x900
	CreateD2DRes(wndhandle, {200,150});

}

D2DHelper::D2DWindow::D2DWindow(HINSTANCE hinst,WNDCLASSEXW wcex)
{
	Instance = hinst;
	{
		ID2D1Factory* f = nullptr;
		if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &f) == S_OK)
			Factory.reset(f);
		else
			abort();
	}
	customwcex = wcex;
	RegisterClassExW(&wcex);
	this->wndhandle = CreateWindowExW(0, customwcex.lpszClassName,
		L"MainD2DWindow",
		WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		1200, 750, 200, 150, 0, 0, this->Instance, 0);//res 1440x900
	CreateD2DRes(wndhandle, {200,150});

}

void D2DHelper::D2DWindow::StartRenderProcess(int nCmdShow)
{
	
	if (wndhandle == INVALID_HANDLE_VALUE)
		abort();
	ShowWindow(wndhandle, nCmdShow);
	UpdateWindow(wndhandle);
}


D2DHelper::D2DWindow::~D2DWindow()
{

}

void D2DHelper::D2DWindow::CreateD2DRes(HWND wndhandle, D2D1_SIZE_U pixelcount)
{
	ID2D1Factory* __raw_factory = nullptr;
	ID2D1HwndRenderTarget* __raw_r_target = nullptr;
	D2D1_RENDER_TARGET_PROPERTIES R_Target_Props =
	{
		D2D1_RENDER_TARGET_TYPE_HARDWARE,
		{
			DXGI_FORMAT_R8G8B8A8_UINT,
			D2D1_ALPHA_MODE_STRAIGHT
		},
		0.0,0.0,
		D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE,
		D2D1_FEATURE_LEVEL_DEFAULT
	};
	D2D1_HWND_RENDER_TARGET_PROPERTIES R_Hwnd_Target_Props =
	{
		wndhandle,
		pixelcount,
		D2D1_PRESENT_OPTIONS_NONE
	};
	if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &__raw_factory) == S_OK)
		Factory.reset(__raw_factory);
	else
		abort();
	Factory->GetDesktopDpi(&R_Target_Props.dpiX, &R_Target_Props.dpiY);
	if (Factory->CreateHwndRenderTarget(&R_Target_Props, &R_Hwnd_Target_Props, &__raw_r_target) == S_OK)
		RenderTarget.reset(__raw_r_target);
	else
		abort();

}


void D2DHelper::Deleters::FactoryDeleter::operator() (ID2D1Factory* target)
{
	target->Release();
}

D2DHelper::D2DWindowV2::D2DWindowV2(HWND hwnd):D2DWindowV2{}
{
	ID2D1HwndRenderTarget* rawtarget = nullptr;
	if (FAILED(Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE),
		D2D1::HwndRenderTargetProperties(hwnd), &rawtarget)))
		throw exception("Create D2D Render Target Failed", 31);
	RenderTarget.reset(rawtarget);
}

ID2D1HwndRenderTarget* D2DHelper::D2DWindowV2::operator->()
{
	return RenderTarget.get();
}

D2DHelper::D2DWindowV2::D2DWindowV2()
{
	ID2D1Factory* rawfactory = nullptr;
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &rawfactory)))
		throw exception("Create D2D Factory Failed",30);
	Factory.reset(rawfactory);
}
