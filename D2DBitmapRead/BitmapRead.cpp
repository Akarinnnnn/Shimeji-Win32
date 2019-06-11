// BitmapRead.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "BitmapRead.h"
#include <filesystem>
#include "../Exceptions/bmpreader_exception.h"

using namespace std;
using namespace D2DHelper;
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
		throw bmpreader_exception("Create WICFactory Failed", hresult);
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
	using namespace COM_helper;
	unique_com<IWICBitmapDecoder> decoder = nullptr;
	unique_com<IWICBitmapFrameDecode> decoded = nullptr;
	unique_com<IWICFormatConverter> converter = nullptr;
	HRESULT last_result = 0;
	IWICBitmapDecoder* rawdecoder;
	IWICBitmapFrameDecode* rawdecoded = nullptr;
	ID2D1Bitmap* bitmap = nullptr;
	last_result = WICFactory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &rawdecoder);
	if (last_result == S_OK)
	{
		decoder.reset(rawdecoder);
		if (decoder->GetFrame(0, &rawdecoded) != S_OK)
			throw bmpreader_exception("Failed to read bitmap", last_result);
		else
			decoded.reset(rawdecoded);
	}
	else
		throw bmpreader_exception("Failed to create WICDecoder", last_result);
	//转换像素格式
	WICPixelFormatGUID format_guid;
	if (decoded->GetPixelFormat(&format_guid) == S_OK)
	{
		if (format_guid != GUID_WICPixelFormat32bppPRGBA)
		{
			IWICFormatConverter* rawconverter = nullptr;
			last_result = WICFactory->CreateFormatConverter(&rawconverter);
			if (SUCCEEDED(last_result))
			{
				rawconverter->Initialize(decoded.get(), GUID_WICPixelFormat32bppPRGBA, WICBitmapDitherTypeNone
					, nullptr, 0.0, WICBitmapPaletteTypeMedianCut);
				converter.reset(rawconverter);
			}
			else
				throw bmpreader_exception("Failed to Create WICFormatConverter", last_result);
		}
	}
	/////////////
	last_result = RenderTarget->CreateBitmapFromWicBitmap(converter.get(), &bitmap);
	if (last_result == S_OK)
		return bitmap;
	else
		throw bmpreader_exception("Failed to Create D2D Bitmap Object", last_result);
}
