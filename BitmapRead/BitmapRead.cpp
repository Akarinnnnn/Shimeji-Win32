// BitmapRead.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "BitmapRead.h"
using namespace std;
namespace BitmapRead
{
	class BitmapReader : public IBitmapReader
	{
	public:
		BitmapReader(ID2D1RenderTarget* RenderTarget)
		{
			this->RenderTarget = RenderTarget;
		}
	private:
		ID2D1RenderTarget* RenderTarget;
	};

	std::shared_ptr<IBitmapReader> CreateReader(ID2D1RenderTarget* RenderTarget)
	{
		IBitmapReader* raw = new BitmapReader(RenderTarget);
		return make_shared<IBitmapReader>(raw);
	}
}

