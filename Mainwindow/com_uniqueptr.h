#include <memory>
#include <combaseapi.h>
namespace COM_helper
{
	class COM_Deleter
	{
	public:
		inline void operator() (IUnknown* target)
		{
			if (target != nullptr)
				target->Release();
		}
	};
	template <typename T>
	using unique_com = std::unique_ptr<T, COM_Deleter>;
}
