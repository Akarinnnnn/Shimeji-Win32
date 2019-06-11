#include "D2DWindow.h"
#include "Resource.h"
#include <thread>
using namespace std;
using namespace COM_helper;
/*
D2DHelper::D2DWindowV3::D2DWindowV3(HWND hwnd, std::shared_ptr<ID2D1Factory> Factory) :D2DWindowV3{ Factory }
{
	ID2D1HwndRenderTarget* rawtarget = nullptr;
	D2D1_RENDER_TARGET_PROPERTIES rtprops =
	{
		D2D1_RENDER_TARGET_TYPE_HARDWARE,
		{
			DXGI_FORMAT_R8G8B8A8_UNORM,
			D2D1_ALPHA_MODE_PREMULTIPLIED
		}
	};
	RECT cl_area = { 0 };
	::GetClientRect(hwnd, &cl_area);
	auto hresult = Factory->CreateHwndRenderTarget(rtprops,
		D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(cl_area.right - cl_area.left,cl_area.bottom-cl_area.top)), &rawtarget);
	if (FAILED(hresult))
		throw HRESULT_exception("Create D2D Render Target Failed", hresult);//不接异常就会闪退
	RenderTarget.reset(rawtarget);
	{
		unsigned int dpi = 0;
		dpi = GetDpiForWindow(this->RenderTarget->GetHwnd());
		RenderTarget->SetDpi((float)dpi, (float)dpi);
	}

}*/

ID2D1HwndRenderTarget* D2DHelper::D2DWindowV3::render_tgt()
{
	return RenderTarget.get();
}

void D2DHelper::D2DWindowV3::resize(UINT w, UINT h)
{
	//RECT thisrect{ 0 };
	//GetWindowRect(this->wnd_handle, &thisrect);
	SetWindowPos(this->wnd_handle, this->wnd_handle, 0, 0, w, h, SWP_ASYNCWINDOWPOS | SWP_NOMOVE);
}

void D2DHelper::D2DWindowV3::show(int cmdshow)
{
	ShowWindow(this->wnd_handle, cmdshow);
}

void D2DHelper::D2DWindowV3::hide()
{
	ShowWindow(this->wnd_handle, SW_HIDE);
}

void D2DHelper::D2DWindowV3::close()
{
	CloseWindow(this->wnd_handle);
}

LPARAM D2DHelper::D2DWindowV3::run_msgloop()
{
	MSG msg{ 0 };
	while (GetMessageW(&msg, this->wnd_handle, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.lParam;
}

LPARAM D2DHelper::D2DWindowV3::ALL_MSGLOOP()
{
	MSG msg{ 0 };
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.lParam;
}

D2DHelper::D2DWindowV3::~D2DWindowV3()
{
	close();
}

D2DHelper::D2DWindowV3::D2DWindowV3(std::shared_ptr<ID2D1Factory> Factory, HINSTANCE hinstance)
{
	this->wnd_handle = CreateWindowExW(WS_EX_LAYERED, L"Shimeji-Win32 Mainwindow Class", L"wdnm",
		WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CW_USEDEFAULT,
		CW_USEDEFAULT, 150, 200, nullptr, nullptr, hinstance, this);
	this->Factory = Factory;

}

void D2DHelper::D2DWindowV3::on_resize(UINT w, UINT h)
{

}

void D2DHelper::D2DWindowV3::register_wnd_class(HINSTANCE hinstance)
{
	WNDCLASSEXW wc_ex{
		sizeof(WNDCLASSEXW),
		CS_HREDRAW | CS_VREDRAW,
		&D2DWindowV3::wnd_proc,
		0,0,
		hinstance,//传入
		nullptr,
		nullptr,
		CreateSolidBrush(RGB(0,0,0)),
		L"A D2D window",
		L"D2D window class",
		nullptr
	};
	RegisterClassExW(&wc_ex);
}

LRESULT __stdcall D2DHelper::D2DWindowV3::wnd_proc(HWND hwnd, UINT wndmessage, WPARAM wp, LPARAM lp)
{
	using namespace COM_helper;
	//lp = this.
	RECT cl_area;
	LONG wnd_style = 0;
	if (wndmessage == WM_CREATE)
	{
		wnd_style = GetWindowLongW(hwnd, GWL_STYLE);
		wnd_style &= ~(WS_CAPTION | WS_SYSMENU | WS_SIZEBOX);
		SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
		SetWindowLongW(hwnd, GWL_STYLE, wnd_style);
		SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(reinterpret_cast<LPCREATESTRUCTW>(lp)->lpCreateParams));
		return 1;
	}
	else
	{
		D2DWindowV3* _this = reinterpret_cast<D2DWindowV3*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
		switch (wndmessage)
		{
		case WM_SIZE:
		{
			UINT w = LOWORD(lp), h = HIWORD(lp);
			_this->on_resize(w, h);
			break;
		}
		case WM_PAINT:
		{

			break;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProcW(hwnd, wndmessage, wp, lp);
		}
		return 0;
	}
}
