#pragma once
#include "framework.h"
#include <wtypes.h>
#include "com_uniqueptr.h"
namespace D2DHelper
{
	class D2DWindowV2
	{
	public:
		D2DWindowV2(HWND hwnd, std::shared_ptr<ID2D1Factory> Factory);
		ID2D1HwndRenderTarget* operator->();
		ID2D1HwndRenderTarget* render_tgt();
	protected:
		D2DWindowV2(std::shared_ptr<ID2D1Factory> Factory);
		std::unique_ptr<ID2D1HwndRenderTarget, COM_helper::unique_com<ID2D1HwndRenderTarget>> RenderTarget;
		std::shared_ptr<ID2D1Factory> Factory;
		HWND window;
		virtual void register_wnd_class();
	private:
		static LRESULT __stdcall wnd_proc(HWND hwnd, UINT wndmessage, WPARAM wp, LPARAM lp);
	};
}


