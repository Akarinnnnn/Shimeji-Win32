#include "GDIHelper.h"
#include <string>
bool GDI::WindowClass::Register()
{
	return RegisterClassExW(&basic) != 0;
}

GDI::WindowClass::~WindowClass()
{
}

GDI::WindowClass::WindowClass()
{
	ZeroMemory(&basic, sizeof(basic));
	basic =
	{
			sizeof(WNDCLASSEXW),
			3,
			&DefWindowProcW,
			0,0,
			0,
			0,
			0,
			(HBRUSH)(6),
			L"DefaultMenuName",
			L"GDI::DefaultWindowClass",
			0
	};
}

GDI::WindowClass::WindowClass(HINSTANCE handle) :WindowClass{}//反正也用不到多少次，就尽可能地减少代码体积了
{
	basic.hInstance = handle;
	basic.hIcon = LoadIconW(handle, MAKEINTRESOURCEW(107));
	basic.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	basic.hIconSm = LoadIconW(handle, MAKEINTRESOURCEW(108));
	//检查句柄
	if (basic.hIcon == NULL)
		exit(20);
	if (basic.hCursor == NULL)
		exit(21);
	if (basic.hIconSm == NULL)
		exit(22);
}

GDI::WindowClass::WindowClass(HINSTANCE instance, wchar_t* Name) :WindowClass{instance}
{
	basic.lpszClassName = Name;
}

void GDI::WindowClass::setproc(WNDPROC proc)
{
	basic.lpfnWndProc = proc;
}

GDI::Window::Window()
{
	handle		= nullptr;
	Instance	= nullptr;
	parent		= nullptr;
	menu		= nullptr;
	style_ex	= 0;
	style		= WS_OVERLAPPEDWINDOW;
	x, y, w, h	= 0;
}

GDI::Window::Window(HINSTANCE h, const wchar_t* wcname):Window{}
{
	this->wcname = wcname;
	title = L"Window";
	Instance = h;
}

GDI::Window::Window(HINSTANCE h, const wchar_t* wcname, const wchar_t* title):Window{}
{
	this->wcname = wcname;
	this->title = title;
	Instance = h;
}

void GDI::Window::setstyle(DWORD style_ex, DWORD style)
{
	this->style = style;
	this->style_ex = style_ex;
}

void GDI::Window::setpos(int x, int y)
{
	if (handle == nullptr)
	{
		this->x = x;
		this->y = y;
	}
	else
		MoveWindow(handle, x, y, w, h, TRUE);
}

void GDI::Window::setparent(HWND parent)
{
	this->parent = parent;
}

void GDI::Window::setsize(int width, int height)
{
	if (handle == nullptr)
	{
		w = width;
		h = height;
	}
	else
		MoveWindow(handle, x, y, width, height, TRUE);
}

void GDI::Window::show(int nCmdShow)
{
	handle = CreateWindowExW(style_ex, wcname, title, style, x, y, w, h, parent, menu, Instance, nullptr);
	if (handle == NULL)
	{
		auto errcode = GetLastError();
		wchar_t errstring[10] = { 0 };
		swprintf_s(errstring, L"%d", errcode);
		MessageBoxExW(nullptr, errstring, L"窗口初始化错误", 0, 0);
		abort();
	}
	ShowWindow(handle,nCmdShow);
}

void GDI::Window::close()
{
	CloseWindow(handle);
}

HWND GDI::Window::get()
{
	return handle;
}
