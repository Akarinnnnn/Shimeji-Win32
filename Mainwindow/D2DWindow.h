#pragma once
#include "framework.h"
#include <wtypes.h>
#include "com_uniqueptr.h"
namespace D2DHelper
{
	class D2DWindowV3
	{
	public:
		D2DWindowV3(std::shared_ptr<ID2D1Factory> Factory, HINSTANCE);
		ID2D1HwndRenderTarget* render_tgt();
		void resize(UINT w, UINT h);
		void show(int cmdshow);
		void hide();
		void close();
		LPARAM run_msgloop();//一个线程一个窗口时用
		[[nodiscard]] static LPARAM ALL_MSGLOOP();//主线程处理所有窗口
		~D2DWindowV3();
	protected:
		COM_helper::unique_com<ID2D1HwndRenderTarget> RenderTarget;
		std::shared_ptr<ID2D1Factory> Factory;
		void on_resize(UINT w, UINT h);
		HWND wnd_handle;
		virtual void register_wnd_class(HINSTANCE);//自行设计
	private:
		static LRESULT __stdcall wnd_proc(HWND, UINT, WPARAM, LPARAM);//子类的窗口过程需要自行设计
	};
}


