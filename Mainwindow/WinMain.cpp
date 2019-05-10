#include "framework.h"
#include <string>
#include "../D2DBitmapRead/BitmapRead.h"
#include "D2DWindow.h"
std::shared_ptr<ID2D1Factory> D2DFactory;

LRESULT __stdcall ShimejiWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static D2DHelper::D2DWindowV2* D2DWindow = nullptr;
	static D2DHelper::bmpreader reader;
	switch (message)
	{
	case 0x00001111://Init D2D
		D2DWindow = reinterpret_cast<D2DHelper::D2DWindowV2*>(lParam);
		reader = D2DHelper::bmpreader::bmpreader(D2DWindow->get());
		break;
	case 0x00001112://Reset
		D2DWindow->get()->BeginDraw();
		D2DWindow->get()->Clear({ 225,225,225,0 });
		D2DWindow->get()->EndDraw();
		SendMessageW(hWnd, WM_PAINT, wParam, lParam);
			break;
	case WM_PAINT:
		D2DWindow->get()->BeginDraw();

		D2DWindow->get()->EndDraw();
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

using namespace std;

std::shared_ptr<ID2D1Factory> CreateFactory()
{
	ID2D1Factory* rawfactory = nullptr;
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &rawfactory)))
		throw exception("Create D2D Factory failed.", 30);
	return shared_ptr<ID2D1Factory>(rawfactory, D2DHelper::D2DObjectDeleter<ID2D1Factory>());
}

int __stdcall wWinMain(HINSTANCE instance, HINSTANCE previnst, wchar_t* cmdline, int cmdshow)
{
	RegisterShimejiWndClass(instance);
	auto mainwindow = CreateWindowExW(0, L"Shimeji-Win32 Mainwindow Class", L"wdnm",
		/*WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS*/
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		0, 150, 200, nullptr, nullptr, instance, nullptr);
	
	if (mainwindow == NULL)
		return 20;
	D2DFactory = CreateFactory();
	D2DHelper::D2DWindowV2 Window(mainwindow,D2DFactory);
	ShowWindow(mainwindow, cmdshow);
	SendMessageW(mainwindow, 0x00001111, NULL, reinterpret_cast<LPARAM>(&Window));
	
	
	
	MSG msg;
	while (GetMessageW(&msg,nullptr,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return (int) msg.wParam;
}
