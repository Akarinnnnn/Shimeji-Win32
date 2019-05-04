#include "GDIHelper.h"

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
			0,
			&DefWindowProcW,
			0,0,
			0,
			0,
			0,
			0,
			MAKEINTRESOURCEW(109),
			L"GDI::DefaultWindowClass",
			0
	};
}
