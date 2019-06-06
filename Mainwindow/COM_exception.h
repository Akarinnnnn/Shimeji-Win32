#pragma once
#include <exception>
#include <wtypes.h>
namespace COM_Helper
{
	class HRESULT_exception :public std::exception
	{
	public:
		HRESULT_exception(const char* msg, HRESULT h) noexcept;
		HRESULT_exception(const char* msg) noexcept;
		/*
		Êä³ö£º
		HRESULT_exception message: ...
			HRESULT message: ...
			HRESULT = 0x12345678
		*/
		virtual char* what() noexcept;
		HRESULT hresult() noexcept;
		~HRESULT_exception() noexcept;
	private:
		char* out_msg;
		const char* msg;
		HRESULT h;
	};
}

