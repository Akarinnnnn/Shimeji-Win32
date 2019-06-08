#include "pch.h"
#include "bmpreader_exception.h"
#include <stdio.h>

D2DHelper::bmpreader_exception::bmpreader_exception(char const* msg, HRESULT id) noexcept : HRESULT_exception{ msg,id }
{
	bmpmsg = nullptr;
}

D2DHelper::bmpreader_exception::bmpreader_exception(char const* msg) noexcept : HRESULT_exception{ msg }
{
	bmpmsg = nullptr;
}

D2DHelper::bmpreader_exception::~bmpreader_exception()
{
	delete[] bmpmsg;
}

char* D2DHelper::bmpreader_exception::what() noexcept
{
	auto size = strlen(msg) + 100 + 20 + 10;
	bmpmsg = new char[size];
	build_hresult_msg();
	sprintf_s(bmpmsg, size, "bmpreader_exception: %s \n\tHRESULT message: %s \n\tHRESULT = 0x%08X", this->msg, this->hresult_msg, this->h);
	return this->bmpmsg;
}
