#include "framework.h"
#include <future>
#include <string>
#include <thread>
#include "../D2DBitmapRead/BitmapRead.h"
#include <dwmapi.h>
#include "D2DWindow.h"
#include "com_uniqueptr.h"
#include "../Exceptions/HRESULT_exception.h"
std::shared_ptr<ID2D1Factory> D2DFactory;

LRESULT __stdcall ShimejiWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	using namespace COM_helper;
	static D2DHelper::D2DWindowV2* D2DWindow = nullptr;
	static D2DHelper::bmpreader reader;
	unique_com<ID2D1Bitmap> bmp;
	RECT cl_area;
	LONG wnd_style = 0;
	
	switch (message)
	{
	case WM_CREATE:
		wnd_style = GetWindowLongW(hWnd, GWL_STYLE);
		wnd_style &= ~(WS_CAPTION | WS_SYSMENU | WS_SIZEBOX);
		SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
		SetWindowLongW(hWnd, GWL_STYLE, wnd_style);
		//0x16010000
		break;
	case 0x00001111://Init D2D
		D2DWindow = reinterpret_cast<D2DHelper::D2DWindowV2*>(lParam);
		reader = D2DHelper::bmpreader::bmpreader(D2DWindow->render_tgt());
	case 0x00001112://Reset
		D2DWindow->render_tgt()->BeginDraw();
		D2DWindow->render_tgt()->Clear({ 225,225,225,255 });
		D2DWindow->render_tgt()->EndDraw();
			break;
	case WM_PAINT:
		bmp.reset(reader.read(L"misc\\»¬»ü.jpg"));		
		SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
		D2DWindow->render_tgt()->BeginDraw();
		D2DWindow->render_tgt()->Clear({ 225,225,225,0 });
		D2DWindow->render_tgt()->DrawBitmap(bmp.get());
		D2DWindow->render_tgt()->EndDraw();
		break;
	case WM_SIZE:
		GetClientRect(hWnd, &cl_area);
		if (D2DWindow != nullptr) D2DWindow->render_tgt()->Resize(D2D1::SizeU(cl_area.right - cl_area.left, cl_area.bottom - cl_area.top));
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
	wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wcex.lpszMenuName = L"Shimeji-Win32 Mainwindow";
	wcex.lpszClassName = L"Shimeji-Win32 Mainwindow Class";
	wcex.hIconSm = nullptr;
	if (RegisterClassExW(&wcex) == 0)
	{
		throw std::exception("Register Window Class Failed");
	}
}

using namespace std;

WPARAM msgloop_fn()
{
	MSG msg;
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.lParam;
}

std::shared_ptr<ID2D1Factory> CreateFactory()
{
	ID2D1Factory* rawfactory = nullptr;
	HRESULT last_result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &rawfactory);
	if (FAILED(last_result))
		throw COM_helper::HRESULT_exception("Create D2D Factory failed.", last_result);
	return shared_ptr<ID2D1Factory>(rawfactory, D2DHelper::D2DObjectDeleter<ID2D1Factory>());
}

int __stdcall wWinMain(HINSTANCE instance, HINSTANCE previnst, wchar_t* cmdline, int cmdshow)
{
	RegisterShimejiWndClass(instance);
	auto mainwindow = CreateWindowExW(WS_EX_LAYERED, L"Shimeji-Win32 Mainwindow Class", L"wdnm",
		WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CW_USEDEFAULT,
		CW_USEDEFAULT, 150, 200, nullptr, nullptr, instance, nullptr);
	MARGINS margins = { -1,0,0,0 };
	if (mainwindow == NULL)
		return 20;
	D2DFactory = CreateFactory();
	
	D2DHelper::D2DWindowV2 Window(mainwindow,D2DFactory);
	ShowWindow(mainwindow, cmdshow);
	SendMessageW(mainwindow, 0x00001111, NULL, reinterpret_cast<LPARAM>(&Window));
	SendMessageW(mainwindow, WM_PAINT, NULL, NULL);
	
	return (int)msgloop_fn();
}

