#pragma once
namespace D2DHelper
{
	template <typename D2DObject>
	class D2DObjectDeleter
	{
	public:
		inline void operator() (D2DObject* target)
		{
			target->Release();
		}
	};
}