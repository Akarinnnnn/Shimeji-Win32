#pragma once
#include <Windows.h>

namespace GDI
{
	class WindowClass
	{
	public:
		bool Register();
		~WindowClass();
		WindowClass();
		WindowClass(HINSTANCE handle);
		WindowClass(HINSTANCE handle, wchar_t* Name);
		void setproc(WNDPROC proc);
	private:
		WNDCLASSEXW basic;
	protected:
	};
	class Window
	{
	public:
		Window();
		Window(HINSTANCE hinst,const wchar_t* wcname);
		Window(HINSTANCE hinst,const wchar_t* wcname, const wchar_t* title);
		void setstyle(DWORD style_ex, DWORD style);
		void setpos(int x, int y);
		void setparent(HWND parent);
		void setsize(int width, int height);
		void show(int nCmdShow);
		void close();
		HWND get();
	private:
		HWND handle, parent;
		HMENU menu;
		HINSTANCE Instance;
		DWORD style;
		DWORD style_ex;
		int x, y, w, h;
		const wchar_t* wcname;
		const wchar_t* title;
	protected:
	};
}