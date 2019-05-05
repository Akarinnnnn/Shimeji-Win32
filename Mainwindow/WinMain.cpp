#include "framework.h"
//#include "D2DWindow.h"
#include "GDIHelper.h"

LRESULT __stdcall wdnmd_wndproc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC DeviceContext = nullptr;
	wchar_t wdnmd[] = L"WDNMD";
	switch (msg)
	{
	case WM_PAINT:
		PAINTSTRUCT ps;
		DeviceContext = BeginPaint(handle, &ps);
		DrawTextExW(DeviceContext, wdnmd, 6, &ps.rcPaint, DT_CENTER, nullptr);
		EndPaint(handle, &ps);
		break;
	case WM_CLOSE:
		PostQuitMessage(900);
		break;
	default:
		DefWindowProcW(handle, msg, wp, lp);
		break;
	}
	return 0;
}

int __stdcall wWinMain(HINSTANCE instance, HINSTANCE previnst, wchar_t* cmdline, int cmdshow)
{
	MSG msg;
	wchar_t wndclassname[] = L"WDNMD";
	wchar_t wndtitle[] = L"Œ“≤›¡À∂º";
	GDI::WindowClass WDNMD_wndclass(instance, wndclassname);
	WDNMD_wndclass.setproc(&::wdnmd_wndproc);
	if (!WDNMD_wndclass.Register())
		return 0x0000F000;
	GDI::Window Mainwindow(instance, wndclassname, wndtitle);
	Mainwindow.setsize(400, 400);
	Mainwindow.setpos(120, 100);
	Mainwindow.show(cmdshow);
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}
