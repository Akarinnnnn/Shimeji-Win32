#include "D2DWindow.h"
#include "Resource.h"
#include <thread>
using namespace std;

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
	auto hresult = Factory->CreateHwndRenderTarget(rtprops,
		D2D1::HwndRenderTargetProperties(hwnd), &rawtarget);
	if (FAILED(hresult))
		throw exception("Create D2D Render Target Failed", 31);
	RenderTarget.reset(rawtarget);
	{
		float dpix, dpiy = 0;
		this->Factory->GetDesktopDpi(&dpix, &dpiy);
		RenderTarget->SetDpi(dpix, dpiy);
	}

}

ID2D1HwndRenderTarget* D2DHelper::D2DWindowV2::operator->()
{
	return RenderTarget.get();
}

ID2D1HwndRenderTarget* D2DHelper::D2DWindowV2::get()
{
	return RenderTarget.get();
}

D2DHelper::D2DWindowV2::D2DWindowV2(std::shared_ptr<ID2D1Factory> Factory)
{
	this->Factory = Factory;
}
