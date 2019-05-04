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
	private:
		WNDCLASSEXW basic;
	protected:
	};
}