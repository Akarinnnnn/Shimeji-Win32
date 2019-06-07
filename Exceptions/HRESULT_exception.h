#pragma once
#include <exception>
#include <wtypes.h>
namespace COM_helper
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
	protected:
		void build_hresult_msg() noexcept;
		char hresult_msg[100 + 20] = { 0 };
		const char* msg;
		HRESULT h;
	private:
		char* out_msg;
	};
}

