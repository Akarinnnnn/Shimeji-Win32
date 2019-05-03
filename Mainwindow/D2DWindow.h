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
	class D2DWindow
	{
	public:
		D2DWindow(HINSTANCE handle);
		void Render();
		~D2DWindow();
	protected:
		HINSTANCE Instance;
		std::unique_ptr < ID2D1Factory, Deleters::FactoryDeleter > Factory;
		virtual BOOL WindowProcess(HWND, UINT, WPARAM, LPARAM);
	};
}


