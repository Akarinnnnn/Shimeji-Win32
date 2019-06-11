#pragma once
#include <exception>
#include <wtypes.h>


#if EXCEPTIONS_EXPORTS
#define EXPORTS __declspec(dllexport)
#else
#define EXPORTS __declspec(dllimport)
#endif // EXCEPTIONS_EXPORTS

namespace COM_helper
{
	class EXPORTS HRESULT_exception :public std::exception
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
		virtual char const* what() const noexcept override;
		HRESULT hresult() noexcept;
		~HRESULT_exception() noexcept override;
	protected:
		void build_hresult_msg() noexcept;
		char hresult_msg[100 + 20] = { 0 };
		const char* msg;
		HRESULT h;
	private:
		void build_out_msg(size_t msg_len);
		char* out_msg;
	};
}

