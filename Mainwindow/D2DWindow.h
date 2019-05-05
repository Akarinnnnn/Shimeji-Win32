#pragma once
#include "framework.h"
#include "D2DObjUtil.h"
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
		std::unique_ptr<ID2D1HwndRenderTarget, D2DObjectDeleter<ID2D1HwndRenderTarget>>
			RenderTarget;
		HWND wndhandle;
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
		std::unique_ptr < ID2D1Factory, D2DObjectDeleter<ID2D1Factory> > Factory;
	private:
		void CreateD2DRes(HWND wndhandle, D2D1_SIZE_U pixelcount);
	};

	class D2DWindowV2
	{
	public:
		D2DWindowV2(HWND hwnd);
		ID2D1HwndRenderTarget* operator->();
	private:
		D2DWindowV2();

		std::unique_ptr<ID2D1Factory, D2DObjectDeleter<ID2D1Factory>> Factory;
		std::unique_ptr<ID2D1HwndRenderTarget, D2DObjectDeleter<ID2D1HwndRenderTarget>> RenderTarget;

	protected:
	};
}


