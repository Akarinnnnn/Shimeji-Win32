#pragma once
#include "framework.h"

#include "D2DObjUtil.h"
namespace D2DHelper
{
	class D2DWindowV2
	{
	public:
		D2DWindowV2(HWND hwnd, std::shared_ptr<ID2D1Factory> Factory);
		ID2D1HwndRenderTarget* operator->();
	private:
		D2DWindowV2(std::shared_ptr<ID2D1Factory> Factory);

		std::shared_ptr<ID2D1Factory> Factory;
		std::unique_ptr<ID2D1HwndRenderTarget, D2DObjectDeleter<ID2D1HwndRenderTarget>> RenderTarget;

	protected:
	};
}


