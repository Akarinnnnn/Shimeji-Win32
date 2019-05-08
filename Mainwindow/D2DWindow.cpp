#include "D2DWindow.h"
#include "Resource.h"
#include <thread>
using namespace std;

D2DHelper::D2DWindowV2::D2DWindowV2(HWND hwnd, std::shared_ptr<ID2D1Factory> Factory):D2DWindowV2{Factory}
{
	ID2D1HwndRenderTarget* rawtarget = nullptr;
	if (FAILED(Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE),
		D2D1::HwndRenderTargetProperties(hwnd), &rawtarget)))
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

D2DHelper::D2DWindowV2::D2DWindowV2(std::shared_ptr<ID2D1Factory> Factory)
{
	this->Factory = Factory;
}
