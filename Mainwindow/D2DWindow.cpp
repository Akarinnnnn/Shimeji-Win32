#include "D2DWindow.h"
#include "Resource.h"
#include <thread>
using namespace std;
using namespace COM_helper;
D2DHelper::D2DWindowV2::D2DWindowV2(HWND hwnd, std::shared_ptr<ID2D1Factory> Factory):D2DWindowV2{Factory}
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

}

ID2D1HwndRenderTarget* D2DHelper::D2DWindowV2::operator->()
{
	return RenderTarget.get();
}

ID2D1HwndRenderTarget* D2DHelper::D2DWindowV2::render_tgt()
{
	return RenderTarget.get();
}

D2DHelper::D2DWindowV2::D2DWindowV2(std::shared_ptr<ID2D1Factory> Factory)
{
	this->Factory = Factory;
}
