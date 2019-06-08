#pragma once
#include "HRESULT_exception.h"

#if EXCEPTIONS_EXPORTS
#define EXPORTS __declspec(dllexport)
#else
#define EXPORTS __declspec(dllimport)
#endif // EXCEPTIONS_EXPORTS
namespace D2DHelper
{
	class EXPORTS bmpreader_exception :public COM_helper::HRESULT_exception
	{
	public:
		bmpreader_exception(char const* msg, HRESULT id) noexcept;
		bmpreader_exception(char const* msg) noexcept;
		~bmpreader_exception();
		char* what() noexcept;
	private:
		char* bmpmsg;
	};
}