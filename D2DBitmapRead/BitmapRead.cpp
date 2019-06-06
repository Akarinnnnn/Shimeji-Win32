// BitmapRead.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "BitmapRead.h"
#include <filesystem>

using namespace std;

D2DHelper::bmpreader::bmpreader()
{
	LPVOID rawfactory = nullptr;
	RenderTarget = nullptr;
	MULTI_QI queryinfo = { 0 };
	auto hresult = CoCreateInstance(
		CLSID_WICImagingFactory2,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory2,
		&rawfactory);
	if(FAILED(hresult))
	{
		throw bmpreader_exception("Create WICFactory Failed", 41);
	}
	else
	{
		WICFactory.reset(reinterpret_cast<IWICImagingFactory2*>(rawfactory));
	}
}

D2DHelper::bmpreader::bmpreader(ID2D1RenderTarget* RenderTarget) : bmpreader{}
{
	this->RenderTarget = RenderTarget;
}

ID2D1Bitmap* D2DHelper::bmpreader::read(const wchar_t * filename)
{
	unique_ptr<IWICBitmapDecoder,COMDeleter> decoder = nullptr;
	unique_ptr<IWICBitmapFrameDecode,COMDeleter> decoded = nullptr;
	unique_ptr<IWICFormatConverter,COMDeleter> converter = nullptr;
	IWICBitmapDecoder* rawdecoder;
	IWICBitmapFrameDecode* rawdecoded = nullptr;
	ID2D1Bitmap* bitmap = nullptr;
	if (WICFactory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &rawdecoder) == S_OK)
	{
		decoder.reset(rawdecoder);
		if (decoder->GetFrame(0, &rawdecoded) != S_OK)
			throw bmpreader_exception("Failed to read bitmap", 41);
		else
			decoded.reset(rawdecoded);
	}
	else
		throw bmpreader_exception("Failed to create WICDecoder", 40);
	//转换像素格式
	WICPixelFormatGUID format_guid;
	if (decoded->GetPixelFormat(&format_guid) == S_OK)
	{
		if (format_guid != GUID_WICPixelFormat32bppPRGBA)
		{
			IWICFormatConverter* rawconverter = nullptr;
			if (WICFactory->CreateFormatConverter(&rawconverter) == S_OK)
			{
				rawconverter->Initialize(decoded.get(), GUID_WICPixelFormat32bppPRGBA, WICBitmapDitherTypeNone
					, nullptr, 0.0, WICBitmapPaletteTypeMedianCut);
				converter.reset(rawconverter);
			}
			else
				throw bmpreader_exception("Failed to Create WICFormatConverter", 43);
		}
	}
	/////////////
	if (RenderTarget->CreateBitmapFromWicBitmap(converter.get(), &bitmap) == S_OK)
		return bitmap;
	else
		throw bmpreader_exception("Failed to Create D2D Bitmap Object", 42);
}

D2DHelper::bmpreader_exception::bmpreader_exception(char const* msg, HRESULT id) noexcept: HRESULT_exception{ msg,id } 
{
	bmpmsg = nullptr;
}

D2DHelper::bmpreader_exception::bmpreader_exception(char const* msg) noexcept : HRESULT_exception{ msg }
{
	bmpmsg = nullptr;
}

char* D2DHelper::bmpreader_exception::what() noexcept
{
	
}
