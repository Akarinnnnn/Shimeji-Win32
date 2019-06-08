#include "pch.h"

#include "HRESULT_exception.h"
#include <stdio.h>
using namespace COM_helper;
HRESULT_exception::HRESULT_exception(const char* msg, HRESULT h) noexcept:HRESULT_exception{msg} 
{
	this->h = h;
}

HRESULT_exception::HRESULT_exception(const char* msg) noexcept
{
	this->h = E_FAIL;
	this->out_msg = nullptr;
	this->msg = msg;
}

char* HRESULT_exception::what() noexcept
{
	size_t msglen = strlen(msg);
	this->out_msg = new char[28 + msglen + 100 + 20 + 14];
	sprintf_s(out_msg,
		msglen + 120,
		"HRESULT_exception message: %s \n\tHRESULT message: %s \n\tHRESULT = 0x%08X\n", 
		this->msg, 
		hresult_msg, 
		this->h);
	return this->out_msg;
}

HRESULT HRESULT_exception::hresult() noexcept
{
	return this->h;
}

HRESULT_exception::~HRESULT_exception() noexcept
{
	delete[] out_msg;
}

void COM_helper::HRESULT_exception::build_hresult_msg() noexcept
{
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, this->h, GetUserDefaultLangID(), hresult_msg, 120, nullptr);
}
