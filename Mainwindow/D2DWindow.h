#pragma once
#include "framework.h"
namespace D2DHelper
{
	namespace Deleters
	{
		class FactoryDeleter
		{
		public: 
			void operator() (ID2D1Factory* target);
		};
	}
	LRESULT __stdcall DefaultWindowProcess(HWND, UINT, WPARAM, LPARAM);
	class D2DWindow
	{
	public:
		D2DWindow(HINSTANCE handle);
		D2DWindow(HINSTANCE handle, WNDCLASSEXW wcex);
		void StartRenderProcess(int nCmdShow);
		~D2DWindow();
	protected:
		static inline WNDCLASSEXW defwcex =
		{
			sizeof(WNDCLASSEXW),
			0,
			&(D2DHelper::DefaultWindowProcess),
			0,0,
			0,
			0,
			0,
			0,
			MAKEINTRESOURCEW(109),
			L"D2DHelper::D2DWindow::DefaultD2DWindowClassEX",
			0
		};
		WNDCLASSEXW customwcex;
		HINSTANCE Instance;
		std::unique_ptr < ID2D1Factory, Deleters::FactoryDeleter > Factory;
	};
}


